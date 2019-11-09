import java.io.IOException;
import java.util.List;
import java.util.ArrayList;

public class ReverseSum {
    public static void main(String[] args) {

        FastScanner scan = new FastScanner(System.in);
        List<List<Integer>> curList = new ArrayList<>();

        try {
            String tempString;
            while ((tempString = scan.nextLine()) != null) {
                curList.add(scan.addArray(tempString));
            }
            scan.close();
        } catch (IOException error) {
            System.out.println(error.getMessage());
        }

        int[] col = new int[scan.maxLength];
        int[] str = new int[curList.size()];

        for (int i = 0; i < curList.size(); i++) {
            for (int j = 0; j < curList.get(i).size(); j++) {
                str[i] += curList.get(i).get(j);
                col[j] += curList.get(i).get(j);
            }
        }

        for (int i = 0; i < curList.size(); i++) {
            for (int j = 0; j < curList.get(i).size(); j++) {
                System.out.print(str[i] + col[j] - curList.get(i).get(j) + " ");
            }
            System.out.println();
        }
    }
}