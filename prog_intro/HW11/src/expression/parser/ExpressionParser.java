package expression.parser;

import expression.*;

public class ExpressionParser implements Parser {

    private Pointer pointer;

    public TripleExpression parse(String expression) {
        pointer = new Pointer(expression);
        return parseOr();
    }

    private TripleExpression parseOr() {
        TripleExpression result = parseXor();
        while (true) {
            switch (pointer.getType()) {
                case OR:
                    result = new Or(result, parseXor());
                    break;
                default:
                    return result;
            }
        }
    }

    private TripleExpression parseXor() {
        TripleExpression result = parseAnd();
        while (true) {
            switch (pointer.getType()) {
                case XOR:
                    result = new Xor(result, parseAnd());
                    break;
                default:
                    return result;
            }
        }
    }

    private TripleExpression parseAnd() {
        TripleExpression result = parseAddSub();
        while (true) {
            switch (pointer.getType()) {
                case AND:
                    result = new And(result, parseAddSub());
                    break;
                default:
                    return result;
            }
        }
    }

    private TripleExpression parseAddSub() {
        TripleExpression result = parseMulDiv();
        while (true) {
            switch (pointer.getType()) {
                case ADD:
                    result = new Add(result, parseMulDiv());
                    break;
                case SUB:
                    result = new Subtract(result, parseMulDiv());
                    break;
                default:
                    return result;
            }
        }
    }

    private TripleExpression parseMulDiv() {
        TripleExpression result = parseLower();
        while (true) {
            switch (pointer.getType()) {
                case MUL:
                    result = new Multiply(result, parseLower());
                    break;
                case DIV:
                    result = new Divide(result, parseLower());
                    break;
                default:
                    return result;
            }
        }
    }

    private TripleExpression parseLower() {
        TripleExpression result = null;
        switch (pointer.getNext().getType()) {
            case VARIABLE:
                result = new Variable(pointer.getContent());
                pointer.getNext();
                break;
            case CONST:
                result = new Const(Integer.parseUnsignedInt(pointer.getContent()));
                pointer.getNext();
                break;
            case INVERSE:
                result = new Inversion(parseLower());
                break;
            case BRACE_OPN:
                result = parseOr();
                pointer.getNext();
                break;
        }
        return result;
    }
}