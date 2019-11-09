"use strict";
 
let expression = (function () {
 
    let vars = {};
    let operations = {};
    const VARIABLES = ['x', 'y', 'z'];
 
    let Primitive = function () {
        this.prefix = function () {
            return this.value.toString();
        };
        this.toString = function () {
            return this.value.toString();
        };
    };
 
    let Const = function (value) {
        this.value = value;
    };
    Const.prototype = new Primitive();
    Const.prototype.evaluate = function () {
        return this.value;
    };
    Const.prototype.diff = function () {
        return Const.ZERO;
    };
 
    Const.ZERO = new Const(0);
    Const.ONE = new Const(1);
 
    let Variable = function (name) {
        this.value = name;
        this.index = VARIABLES.indexOf(name);
    };
    Variable.prototype = new Primitive();
    Variable.prototype.evaluate = function (...args) {
        return args[this.index];
    };
    Variable.prototype.diff = function (name) {
        return name === this.value ? Const.ONE : Const.ZERO;
    };
 
    VARIABLES.forEach((cur) => {
        vars[cur] = new Variable(cur);
    });
 
    let AbstractOperator = function (symbol, operation, derivative) {
        this.op = function (index) {
            return this.operands[index];
        };
 
        this.prefix = function () {
            return '(' + symbol + ' ' + this.operands.map(elem => elem.prefix()).join(' ') + ')';
        };
 
        this.toString = function () {
            return this.operands.join(' ') + ' ' + symbol;
        };
 
        this.evaluate = function (...args) {
            return operation(...this.operands.map((operand) => operand.evaluate(...args)))
        };
 
        this.diff = function (name) {
            return derivative(name, ...this.operands);
        };
    };
 
    let operatorFactory = function (symbol, operation, derivative) {
        let Operator = function (...args) {
            this.operands = Array.from(args);
        };
        Operator.prototype = new AbstractOperator(symbol, operation, derivative);
        operations[symbol] = {
            op: Operator,
            opLength: operation.length,
        };
        return Operator;
    };
 
    const Negate = operatorFactory(
        'negate',
        (a) => (-a),
        (name, a) => new Negate(a.diff(name))
    );
 
    const Add = operatorFactory(
        '+',
        (a, b) => (a + b),
        (name, a, b) => new Add(a.diff(name), b.diff(name))
    );
 
    const Subtract = operatorFactory(
        '-',
        (a, b) => (a - b),
        (name, a, b) => new Subtract(a.diff(name), b.diff(name))
    );
 
    const Multiply = operatorFactory(
        '*',
        (a, b) => (a * b),
        (name, a, b) => new Add(new Multiply(a, b.diff(name)), new Multiply(a.diff(name), b))
    );
 
    const Divide = operatorFactory(
        '/',
        (a, b) => (a / b),
        (name, a, b) => new Divide(new Subtract(
                    new Multiply(a.diff(name), b),
                    new Multiply(a, b.diff(name))),
                new Multiply(b, b)
            )
    );
 
    const Exp = operatorFactory(
        null,
        (a) => Math.exp(a),
        (name, a) => new Multiply(a.diff(name),new Exp(a))
    );
 
    const Sumexp = operatorFactory(
        'sumexp',
        function (...args) {
            return Array.from(args).reduce((sum, cur) => sum + Math.exp(cur), 0);
        },
        function (name, ...args) {
            return Array.from(args).reduce((sum, operation) => new Add(sum,
                (new Exp(operation)).diff(name)), Const.ZERO);
        }
    );
 
    const Softmax = operatorFactory(
        'softmax',
        function (...args) {
            return Math.exp(args[0]) / Array.from(args).reduce((sum, cur) => sum + Math.exp(cur), 0);
        },
        function (name, ...args) {
            return (new Divide(new Exp(args[0]), new Sumexp(...args))).diff(name);
        }
    );
 
    function applyToConstructor(constructor, args) {
        let temp = Object.create(constructor.prototype);
        constructor.apply(temp, args);
        return temp;
    }
 
    let parse = function (str) {
        let stack = [];
        str.trim().split(/\s+/).forEach(token => {
            if (token in operations) {
                stack.push(applyToConstructor(operations[token].op,
                    stack.splice(stack.length - operations[token].opLength, operations[token].opLength)));
            } else if (VARIABLES.indexOf(token) !== -1) {
                stack.push(vars[token]);
            } else {
                stack.push(new Const(parseInt(token)));
            }
        });
        return stack.pop();
    };
 
    let exceptions = function () {
        let exceptionFactory = function (message) {
            let Exception = function (index, token) {
                this.name = message + " on position " + index + ", where '" + token + "' is";
            };
            Exception.prototype = new Error();
            return Exception;
        };
 
        const ClosingParenthesisMissingException = exceptionFactory(
            'Closing parenthesis expected'
        );
        const ExpressionEndExpectedException = exceptionFactory(
            'End of expression expected'
        );
        const OperationExpectedException = exceptionFactory(
            'Operation symbol expected'
        );
        const OperandExpectedException = exceptionFactory(
            'Operand expected'
        );
        const InvalidOperandsAmountException = exceptionFactory(
            'Invalid operands amount found'
        );
 
        return {
            ClosingParenthesisMissingException: ClosingParenthesisMissingException,
            ExpressionEndExpectedException: ExpressionEndExpectedException,
            OperationExpectedException: OperationExpectedException,
            OperandExpectedException: OperandExpectedException,
            InvalidOperandsAmountException: InvalidOperandsAmountException
        }
    }();
 
    let Tokenizer = function (str) {
        this.index = 0;
        this.token = '';
        let isWhitespace = function (c) {
            return /\s/.test(c);
        };
 
        this.nextToken = function () {
            while (this.index < str.length && isWhitespace(str[this.index])) {
                this.index++;
            }
            this.token = '';
            if (str[this.index] === '(' || str[this.index] === ')') {
                this.token = str[this.index++];
            } else {
                while (this.index < str.length &&
                !isWhitespace(str[this.index]) && str[this.index] !== '(' && str[this.index] !== ')') {
                    this.token += str[this.index++];
                }
            }
        };
    };
 
    let parseOperand = function (tokenizer, parseExpression) {
        if (tokenizer.token === '(') {
            return parseExpression();
        } else if (VARIABLES.indexOf(tokenizer.token) !== -1) {
            let res = vars[tokenizer.token];
            tokenizer.nextToken();
            return res;
        } else if (!isNaN(tokenizer.token) && tokenizer.token !== '') {
            let res = new Const(parseFloat(tokenizer.token));
            tokenizer.nextToken();
            return res;
        } else {
            throw new exceptions.OperandExpectedException(tokenizer.index, tokenizer.token);
        }
    };
 
    let parsePrefix = function (str) {
        let tokenizer = new Tokenizer(str);
 
        let parseExpression = function () {
            if (tokenizer.token === '(') {
                tokenizer.nextToken();
                if (!(tokenizer.token in operations)) {
                    throw new exceptions.OperationExpectedException(tokenizer.index, tokenizer.token);
                }
                let operation = operations[tokenizer.token];
                tokenizer.nextToken();
                let args = [];
                if (operation.opLength === 0) {
                    while (tokenizer.token !== ')' && tokenizer.token !== '') {
                        args.push(parseOperand(tokenizer, parseExpression));
                    }
                } else {
                    for (let i = 0; i < operation.opLength; i++) {
                        args.push(parseOperand(tokenizer, parseExpression));
                    }
                }
                if (tokenizer.token !== ')') {
                    throw new exceptions.ClosingParenthesisMissingException(tokenizer.index, tokenizer.token);
                }
                tokenizer.nextToken();
                return applyToConstructor(operation.op, args);
            } else {
                return parseOperand(tokenizer, parseExpression);
            }
        };
        tokenizer.nextToken();
        let res = parseExpression();
        if (tokenizer.token !== '') {
            throw new exceptions.ExpressionEndExpectedException(tokenizer.index, tokenizer.token);
        }
        return res;
    };
 
    return {
        Const: Const,
        Variable: Variable,
        Negate: Negate,
        Add: Add,
        Subtract: Subtract,
        Multiply: Multiply,
        Divide: Divide,
        Exp: Exp,
        Sumexp: Sumexp,
        Softmax: Softmax,
        parse: parse,
        parsePrefix: parsePrefix,
    }
 
})();
 
 
let Const = expression.Const;
let Variable = expression.Variable;
 
let Negate = expression.Negate;
let Add = expression.Add;
let Subtract = expression.Subtract;
let Multiply = expression.Multiply;
let Divide = expression.Divide;
let Sumexp = expression.Sumexp;
let Softmax = expression.Softmax;
 
let parse = expression.parse;
let parsePrefix = expression.parsePrefix;