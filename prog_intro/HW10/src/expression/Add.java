package expression;

public class Add extends Binary {
    Add(CommonExpression first, CommonExpression second) {
        super(first, second);
    }

    protected int apply(int first, int second) {
        return first + second;
    }

    protected double apply(double first, double second) {
        return first + second;
    }
}