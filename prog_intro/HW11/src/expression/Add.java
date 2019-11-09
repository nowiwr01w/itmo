package expression;

public class Add extends Binary {
    public Add(TripleExpression first, TripleExpression second) {
        super(first, second);
    }

    protected int apply(int first, int second) {
        return first + second;
    }
}