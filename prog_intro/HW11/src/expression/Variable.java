package expression;

public class Variable implements TripleExpression {
    private String var;

    public Variable(String var) {
        assert (var != null) : "Constructed with \"null\" argument";
        this.var = var;
    }

    public int evaluate(int x, int y, int z) {
        switch (var) {
            case "x":
                return x;
            case "y":
                return y;
            case "z":
                return z;
        }
        return 0;
    }
}