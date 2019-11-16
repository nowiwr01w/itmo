const VARIABLES = ['x', 'y', 'z'];

function operation(func) {
    return function () {
        let operands = arguments;
        return function () {
            let result = [];
            for (let i = 0; i < operands.length; i++) {
                result.push(operands[i].apply(null, arguments));
            }
            return func.apply(null, result);
        }
    }
}

function cnst(num) {
    return function() {
        return num;
    }
}

function variable(name) {
    let index = VARIABLES.indexOf(name);
    return function () {
        return arguments[index];
    }
}

const add = operation(function (a, b) {
    return a + b
});
const subtract = operation(function (a, b) {
    return a - b
});
const multiply = operation(function (a, b) {
    return a * b
});
const divide = operation(function (a, b) {
    return a / b
});

const negate = operation(function (a) {
    return -a
})

const abs = operation(function (a) {
    return Math.abs(a);
})

const iff = operation(function () {
    return arguments[0] >= 0 ? arguments[1] : arguments[2]
})


for (let i = 0; i < VARIABLES.length; i++) {
    this[VARIABLES[i]] = variable(VARIABLES[i]);
}

function isDigit(sym) {
    return sym >= '0' && sym <= '9';
}

function parse(expr) {

    let tokens = expr.split(/\s+/);

    let OPERATIONS = {
        '+'      : [add, 2],
        '-'      : [subtract, 2],
        '*'      : [multiply, 2],
        '/'      : [divide, 2],
        'abs'   : [abs, 1],
        'iff'   : [iff, 3],
        'negate' : [negate, 1]
    };

    let stack = [];
    for (let i = 0; i < tokens.length; i++) {
        let token = tokens[i];
        if (token in OPERATIONS) {
            let args = [];
            for (let j = 0; j < OPERATIONS[token][1]; j++) {
                args.push(stack.pop());
            }
            args.reverse();
            stack.push(OPERATIONS[token][0].apply(null, args));
        } else if (isDigit(tokens[i][0]) || (tokens[i][0] === '-' && tokens[i].length !== 1)) {
            stack.push(cnst(parseInt(tokens[i])));
        } else if (VARIABLES.indexOf(tokens[i]) !== -1) {
            stack.push(this[tokens[i]]);
        }
    }
    return stack.pop();
}