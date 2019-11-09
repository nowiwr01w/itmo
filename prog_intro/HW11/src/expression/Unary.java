package expression;

public abstract class Unary implements TripleExpression {
    private TripleExpression expression;

    Unary(TripleExpression expression) {
        this.expression = expression;
    }

    public int evaluate(int x, int y, int z) {
        return apply(expression.evaluate(x, y, z));
    }

    protected abstract int apply(int expression);
}