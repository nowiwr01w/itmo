package expression;

public class Or extends Binary {
    public Or(TripleExpression first, TripleExpression second) {
        super(first, second);
    }

    protected int apply(int first, int second) {
        return first | second;
    }
}