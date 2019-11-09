public class SumDoubleSpace {
    public static void main(String[] args) {
        double sum = 0;
        for (String arg : args) {
            arg += " 0.0";
            for (String s : arg.split("\\p{IsWhite_Space}+")) {
                if (s.isEmpty() == false) {
                    sum += Double.parseDouble(s);
                }
            }
        }
        System.out.println(sum);
    }
}
