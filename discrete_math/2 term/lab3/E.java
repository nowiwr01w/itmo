import java.io.*;
import java.util.*;

public class task_e {

    class FastScanner {
        BufferedReader reader;
        StringTokenizer tokenizer;

        public FastScanner(String fileName) throws IOException {
            reader = new BufferedReader(new FileReader(fileName));
        }

        public FastScanner() throws IOException {
            reader = new BufferedReader(new InputStreamReader(System.in));
        }

        public String next() throws IOException {
            while (tokenizer == null || !tokenizer.hasMoreTokens()) {
                String line = reader.readLine();
                if (line == null) {
                    return null;
                }
                if (line.equals("")) {
                    return "";
                }
                tokenizer = new StringTokenizer(line);
            }
            return tokenizer.nextToken();
        }

        public int nextInt() throws IOException {
            return Integer.parseInt(next());
        }

        public double nextDouble() throws IOException {
            return Double.parseDouble(next());
        }
    }

    class SingleRule {
        int left;
        int right;

        public SingleRule(int left, int right) {
            this.left = left;
            this.right = right;
        }
    }

    class Rule {
        int left;
        int right1;
        int right2;

        public Rule(int left, int right1, int right2) {
            this.left = left;
            this.right1 = right1;
            this.right2 = right2;
        }
    }

    public void solve(PrintWriter out) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("cf.in"));
        String[] a = in.readLine().split(" ");
        int n = Integer.parseInt(a[0]);
        int start = a[1].charAt(0) - 'A';
        ArrayList<Rule> rules = new ArrayList<>();
        HashSet<Integer> epsilonRules = new HashSet<>();
        ArrayList<SingleRule> singleRules = new ArrayList<>();

        int counter = 101;

        for (int i = 0; i < n; i++) {
            String[] str = in.readLine().split(" ");

            int term = str[0].charAt(0) - 'A';
            if (str.length == 2) {
                epsilonRules.add(term);
                continue;
            }
            if (str[2].length() == 1) {
                singleRules.add(new SingleRule(term, str[2].charAt(0) - 'A'));
                continue;
            }
            String s = str[2];
            while (s.length() > 2) {
                rules.add(new Rule(term, counter, s.charAt(s.length() - 1) - 'A'));
                s = s.substring(0, s.length() - 1);
                term = counter++;
            }
            rules.add(new Rule(term, s.charAt(0) - 'A', s.charAt(1) - 'A'));
        }

        String str = in.readLine();
        int strLen = str.length();
        for (int i = 0; i < 1000; i++) {
            for (SingleRule sg : singleRules) {
                if (epsilonRules.contains(sg.right))
                    epsilonRules.add(sg.left);
            }

            for (Rule rule : rules) {
                if (epsilonRules.contains(rule.right1) && epsilonRules.contains(rule.right2))
                    epsilonRules.add(rule.left);
            }
        }



        boolean[][][] dp = new boolean[counter][strLen][strLen];
        for (int i = 0; i < strLen; i++) {
            for (SingleRule sg : singleRules) {
                if (sg.right == str.charAt(i) - 'A') {
                    dp[sg.left][i][i] = true;
                }
            }
            dp[str.charAt(i) - 'A'][i][i] = true;
        }

        for (int ind = 1; ind <= strLen; ind++) {
            for (int i = 0; i <= strLen - ind; i++) {
                int r=i+ind-1;
                for (int j = i; j < r; j++) {
                    for (Rule rule : rules) {
                        if (dp[rule.right1][i][j] && dp[rule.right2][j + 1][r]) {
                            dp[rule.left][i][r] = true;
                        }
                    }

                }
                for (int j = 0; j <20 ; j++) {

                    for (Rule rule : rules) {
                        if (dp[rule.right1][i][r] && epsilonRules.contains(rule.right2)
                                || dp[rule.right2][i][r] && epsilonRules.contains(rule.right1)) {
                            dp[rule.left][i][r] = true;
                        }
                    }
                    for (int k = 0; k < n; k++) {
                        if (dp[k][i][r]) {
                            for (SingleRule sg : singleRules) {
                                if (sg.right == k) {
                                    dp[sg.left][i][r] = true;
                                }
                            }
                        }
                    }
                }
            }
	}

        if (dp[start][0][str.length() - 1])
            out.println("yes");
        else
            out.println("no");

    }


    StreamTokenizer in;
    PrintWriter out;

    void run() throws IOException {
        out = new PrintWriter("cf.out");
        solve(out);
        out.flush();
    }

    public static void main(String[] args) throws IOException {
        new task_e().run();

    }
}