import java.util.*;
 
public class Party {
 
    private static ArrayList<Boolean> used = new ArrayList<>();
    private static ArrayList<Integer> order = new ArrayList<>();
    private static ArrayList<Integer> components = new ArrayList<>();
 
    private static Map<String, Integer> nameToNumber = new HashMap<>();
    private static Map<Integer, String> numberToNames = new HashMap<>();
 
    private static ArrayList<ArrayList<Integer>> graph = new ArrayList<>();
    private static ArrayList<ArrayList<Integer>> reversedGraph = new ArrayList<>();
 
    private static void dfs1(int vertex) {
        used.set(vertex, true);
        for (int u : graph.get(vertex)) {
            if (!used.get(u)) {
                dfs1(u);
            }
        }
        order.add(vertex);
    }
 
    private static void dfs2(int vertex, int color) {
        components.set(vertex, color);
        for (int u : reversedGraph.get(vertex)) {
            if (components.get(u) == -1) {
                dfs2(u, color);
            }
        }
    }
 
    private static void makeChoice(String first, String second) {
        String a, b;
        if (first.charAt(0) == '+' && second.charAt(0) == '+') {
            a = "-" + first.substring(1);
            b = "-" + second.substring(1);
        } else if (first.charAt(0) == '+' && second.charAt(0) == '-') {
            a = "-" + first.substring(1);
            b = "+" + second.substring(1);
        } else if (first.charAt(0) == '-' && second.charAt(0) == '+') {
            a = "+" + first.substring(1);
            b = "-" + second.substring(1);
        } else {
            a = "+" + first.substring(1);
            b = "+" + second.substring(1);
        }
        graph.get(nameToNumber.get(b)).add(nameToNumber.get(a));
        reversedGraph.get(nameToNumber.get(a)).add(nameToNumber.get(b));
    }
 
 
    public static void main(String[] args) {
 
        Scanner in = new Scanner(System.in);
 
        int n = in.nextInt();
        int m = in.nextInt();
 
        for (int i = 0; i < 2 * n; i++) {
            graph.add(new ArrayList<>());
            reversedGraph.add(new ArrayList<>());
        }
 
        for (int i = 0; i < 2 * n; i++) {
            String name = in.next();
            nameToNumber.put("+" + name, i);
            numberToNames.put(i, name);
            nameToNumber.put("-" + name, ++i);
            numberToNames.put(i, name);
        }
 
        for (int i = 0; i < m; i++) {
            String first, second;
            first = in.next();
            in.next();
            second = in.next();
            graph.get(nameToNumber.get(first)).add(nameToNumber.get(second));
            reversedGraph.get(nameToNumber.get(second)).add(nameToNumber.get(first));
            makeChoice(first, second);
        }
 
        for (int i = 0; i < 2 * n; i++) {
            used.add(false);
        }
 
        for (int i = 0; i < 2 * n; i++) {
            components.add(-1);
        }
 
        for (int i = 0; i < 2 * n; i++) {
            if (!used.get(i)) {
                dfs1(i);
            }
        }
 
        int j = 0;
        for (int i = 0; i < 2 * n; i++) {
            int point = order.get(2 * n - 1 - i);
            if (components.get(point) == -1) {
                dfs2(point, j++);
            }
        }
 
        for (int i = 0; i < 2 * n; i++) {
            if (components.get(i).equals(components.get(++i))) {
                System.out.print(-1);
                return;
            }
        }
 
        List<String> result = new ArrayList<>();
        for (int i = 0; i < 2 * n; i++) {
            if (components.get(i) > components.get(++i)) {
                result.add(numberToNames.get(i));
            }
        }
 
        System.out.println(result.size());
        for (String curName : result) {
            System.out.print(curName + " ");
        }
 
    }
}