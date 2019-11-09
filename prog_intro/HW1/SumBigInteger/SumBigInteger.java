import java.math.BigInteger;

public class SumBigInteger {
    public static void main(String[] args) {
        BigInteger sum = BigInteger.ZERO;
        for (String arg : args) {
            for (String cur_str : arg.split("\\p{javaWhitespace}+")) {
                if (!cur_str.isEmpty()) {
                    BigInteger cur_number = new BigInteger(cur_str);
                    sum = sum.add(cur_number);
                }
            }
        }
        System.out.println(sum);
    }
}


