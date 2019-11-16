"use strict"

const VARIABLES = {
	"x": 0,
	"y": 1,
	"z": 2,
}

const inseparable = {simplify: function() {return this} };

function Const(value) {
    this.value = value;
}
Const.prototype = Object.create(inseparable);

const ZERO = new Const(0);
const ONE = new Const(1);

Const.prototype.toString = function() {
    return this.value.toString();
}

Const.prototype.evaluate = function() {
    return this.value;
}

Const.prototype.diff = function() {
	return ZERO;
}

Const.prototype.prefix = function() {
	return this.value.toString();
}

function isZero(a) {
    return ((a instanceof Const) && (a.value === 0));
}
function isOne(a) {
    return ((a instanceof Const) && (a.value === 1));
}
function isConst(a) {
	return (a instanceof Const);
}

function Variable(name) {
	this.name = name
	this.getNumber = function() {
		return VARIABLES[name];
	}
}
Variable.prototype = Object.create(inseparable);

Variable.prototype.toString = function() {
	return this.name;
}

Variable.prototype.evaluate = function() {
	return arguments[this.getNumber()];
}

Variable.prototype.diff = function(d) {
	return d === this.name ? ONE : ZERO; 
}

Variable.prototype.prefix = function() {
	return this.name;
}

function isVariable(a) {
	return (a instanceof Variable);
}

function Operation(action, char, diffRule, simplifyRule, ...operands) {
	this.action = action;
	this.char = char;
	this.operands = operands;
	this.diffRule = diffRule;
	this.simplifyRule = simplifyRule;
}

Operation.prototype.toString = function() {
	return this.operands.join(" ") + " " + this.char;
}

Operation.prototype.evaluate = function() {
	const args = [].slice.call(arguments);
	const result = [];
	this.operands.map(function(operand) { result.push(operand.evaluate(...args)) });
	return this.action(...result);
}

Operation.prototype.diff = function(d) {
	const args = this.operands.concat(this.operands.map(function (operand) { return operand.diff(d) }));
	return this.diffRule(...args);
}

Operation.prototype.simplify = function() {
	const args = this.operands.map(function (operand) { return operand.simplify() });
	return this.simplifyRule(...args);
}

Operation.prototype.prefix = function() {
	return this.char + " " + this.operands.join(" ");
}

Add.prototype = Operation.prototype;
function Add(...args) {
	Operation.call(
			this, 
			(a, b) => a + b, 
			"+", 	
			(a, b, da, db) => new Add(da, db),
			function(a, b) {
				if (isZero(a)) {
					return b;
				}
				if (isZero(b)) {
					return a;
				}
				if (isConst(a) && isConst(b)) {
					return new Const(a.value + b.value);
				}
				return new Add(a, b);
			},
			args[0], args[1]
	);
}

Subtract.prototype = Operation.prototype;
function Subtract(...args) {
	Operation.call(
			this, 
			(a, b) => a - b, 
			"-", 	
			(a, b, da, db) => new Subtract(da, db),
			function(a, b) {
				if (isZero(a)) {
					if (isConst(b)) {
						return new Const(Number(-b));
					} else {
						return new Negate(b);
					}
				}
				if (isZero(b)) {
					return a;
				}
				if (isConst(a) && isConst(b)) {
					return new Const(a.value - b.value);
				}
				return new Subtract(a, b);
			},
			args[0], args[1]
	);
}

Multiply.prototype = Operation.prototype;
function Multiply(...args) {
	Operation.call(
			this, 
			(a, b) => a * b, 
			"*", 	
			(a, b, da, db) => new Add(new Multiply(a, db), new Multiply(b, da)),
			function(a, b) {
				if (isOne(a)) {
					return b;
				}
				if (isOne(b)) {
					return a;
				}
				if (isZero(a) || isZero(b)) {
					return ZERO;
				}
				if (isConst(a) && isConst(b)) {
					return new Const(a.value * b.value);
				}
				return new Multiply(a, b);
			},
			args[0], args[1]
	);
}

Divide.prototype = Operation.prototype;
function Divide(...args) {
	Operation.call(
			this, 
			(a, b) => a / b, 
			"/", 	
			(a, b, da, db) => new Divide(new Subtract(new Multiply(da, b), new Multiply(db, a)), new Multiply(b, b)),
			function(a, b) {
				if (isZero(a)) {
					return ZERO;
				}
				if (isOne(b)) {
					return a;
				}
				if (isConst(a) && isConst(b)) {
					return new Const(a.value / b.value);
				}
				if (isVariable(a) && isVariable(b) && a.name === b.name) {
					return new ONE;
				}
				return new Divide(a, b);
			},
			args[0], args[1]
	);
}

Negate.prototype = Operation.prototype;
function Negate(...args) {
	Operation.call(
			this, 
			a => -a, 
			"negate", 	
			(a, da) => new Negate(da),
			function(a, b) {
				if (isConst(a)) {
					if (isZero(a)) {
						return ZERO;
					} else {
						return new Const(-a);
					}
				}
				return new Negate(a);
			},
			args[0]
	);
}

ArcTan.prototype = Operation.prototype;
function ArcTan(...args) {
	Operation.call(
			this,
			a => Math.atan(a),
			"atan",
			(a, da) => new Divide(da, new Add(ONE, new Multiply(a, a))),
			function(a) {
				if (isConst(a)) {
					return new Const(Math.atan(a.value));
				}
				return new ArcTan(a);
			},
			args[0]
	);
}

ArcTan2.prototype = Operation.prototype;
function ArcTan2(...args) {
	Operation.call(
			this,
			(a, b) => Math.atan2(a, b),
			"atan2",
			(a, b, da, db) => new Divide(new Subtract(new Multiply(da, b), new Multiply(db, a)), new Add(new Multiply(a, a), new Multiply(b, b))),
			function(a, b) {
				if (isConst(a) && isConst(b)) {
					return new Const(Math.atan2(a.value, b.value));
				}
				if (isZero(a)) {
					return new ArcTan(ZERO);
				}
				if (isOne(b)) {
					return new ArcTan(a);
				}
				return new ArcTan2(a, b);
			},
			args[0], args[1]
	);
}

Sinh.prototype = Operation.prototype;
function Sinh(...args) {
	Operation.call(
			this,
			a => Math.sinh(a),
			"sinh",
			(a, da) => new Multiply(da, new Cosh(a)),
			function(a) {
				if (isConst(a)) {
					return new Const(Math.sinh(a.value));
				}
				return new Sinh(a);
			},
			args[0]
	);
}

Cosh.prototype = Operation.prototype;
function Cosh(...args) {
	Operation.call(
			this,
			a => Math.cosh(a),
			"cosh",
			(a, da) => new Multiply(da, new Sinh(a)),
			function(a) {
				if (isConst(a)) {
					return new Const(Math.cosh(a.value));
				}
				return new Cosh(a);
			},
			args[0]
	);
}

const parse = function(s) {
    const tokens = s.split(" ").filter(function (token) {
        return token.length > 0;
    });

    let stack = [];
    const OPER = {
        "+": Add,
        "-": Subtract,
        "*": Multiply,
        "/": Divide,
        "negate": Negate,
        "atan": ArcTan,
        "atan2": ArcTan2,
        "sinh": Sinh,
        "cosh": Cosh,
    };

    const AMT_ARGS = {
        "+": 2,
        "-": 2,
        "*": 2,
        "/": 2,
        "negate": 1,
        "atan": 1,
        "atan2": 2,
        "sinh": 1,
        "cosh": 1,
    };

    tokens.map(function(token) {
    	if (token in VARIABLES) {
            stack.push(new Variable(token));
        } else if (token in OPER) {
        	const args = stack.slice(stack.length - AMT_ARGS[token], stack.length);
        	stack = stack.slice(0, stack.length - AMT_ARGS[token]);
            stack.push(new OPER[token](...args));
        } else {
        	stack.push(new Const(parseInt(token)));
        }
    });

    return stack.pop();
}