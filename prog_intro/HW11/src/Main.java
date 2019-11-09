import expression.TripleExpression;
import expression.parser.ExpressionParser;
import expression.parser.Parser;

public class Main {
    public static void main(String[] args) {
        Parser parser = new ExpressionParser();
        TripleExpression ans = parser.parse("");
        System.out.println(ans.evaluate(1, 1, 1));
    }
}
