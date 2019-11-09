package expression.parser;

class Pointer {
    enum Type {
        INIT, END,
        OR, XOR, AND,
        ADD, SUB,
        MUL, DIV,
        BRACE_OPN, BRACE_CLS, INVERSE, CONST, VARIABLE
    }

    private Type type;
    private int begin, end;
    private final String expression;

    Pointer(String expression) {
        this.expression = expression;
        this.begin = this.end = 0;
        this.type = Type.INIT;
    }

    private void skipWhiteSpace() {
        while (begin < expression.length() && Character.isWhitespace(expression.charAt(begin))) {
            ++begin;
        }
    }

    String getContent() {
        return expression.substring(begin, end);
    }

    Type getType() {
        return type;
    }

    Pointer getNext() {
        begin = end;
        skipWhiteSpace();
        if (begin >= expression.length()) {
            type = Type.END;
            return this;
        }
        end = begin + 1;
        switch (expression.charAt(begin)) {
            case '|':
                type = Type.OR;
                break;
            case '^':
                type = Type.XOR;
                break;
            case '&':
                type = Type.AND;
                break;
            case '+':
                type = Type.ADD;
                break;
            case '-':
                if (type == Type.CONST || type == Type.VARIABLE || type == Type.BRACE_CLS) {
                    type = Type.SUB;
                } else {
                    type = Type.INVERSE;
                }
                break;
            case '*':
                type = Type.MUL;
                break;
            case '/':
                type = Type.DIV;
                break;
            case '(':
                type = Type.BRACE_OPN;
                break;
            case ')':
                type = Type.BRACE_CLS;
                break;
            default:
                if (Character.isDigit(expression.charAt(begin))) {
                    while (end < expression.length() && Character.isDigit(expression.charAt(end))) {
                        ++end;
                    }
                    type = Type.CONST;
                } else {
                    type = Type.VARIABLE;
                }
        }
        return this;
    }
}