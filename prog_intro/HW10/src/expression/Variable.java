package expression;

public class Variable implements CommonExpression {
    private String var;

    Variable(String var) {
        assert var != null;
        this.var = var;
    }

    public int evaluate(int x) {
        return x;
    }

    public double evaluate(double x) {
        return x;
    }

    public int evaluate(int x, int y) {
        switch (var) {
            case "x":
                return x;
            case "y":
                return y;
        }
        return 0;
    }
}