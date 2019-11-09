package expression;

public abstract class Binary implements TripleExpression {
    private TripleExpression first;
    private TripleExpression second;

    Binary(TripleExpression first, TripleExpression second) {
        assert (first != null) && (second != null);
        this.first = first;
        this.second = second;
    }

    public int evaluate(int x, int y, int z) {
        return apply(first.evaluate(x, y, z), second.evaluate(x, y, z));
    }

    protected abstract int apply(int first, int second);
}