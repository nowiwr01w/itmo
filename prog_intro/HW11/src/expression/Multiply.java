package expression;

public class Multiply extends Binary {
    public Multiply(TripleExpression first, TripleExpression second) {
        super(first, second);
    }

    protected int apply(int first, int second) {
        return first * second;
    }
}