import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class ReverseTranspose {
    public static void main(String[] args) {

        int maxString = 0;
        Scanner in = new Scanner(System.in);
        List<List<Integer>> curArray = new ArrayList<>();

        while (in.hasNextLine()) {
            List<Integer> line = new ArrayList<>();
            Scanner currentLine = new Scanner(in.nextLine());
            while (currentLine.hasNextInt()) {
                line.add(currentLine.nextInt());
            }
            curArray.add(line);
            maxString = Math.max(maxString, line.size());
        }

        for (int i = 0; i < maxString; i++) {
            for (int j = 0; j < curArray.size(); j++) {
                if (curArray.size() > j) {
                    if (curArray.get(j).size() > i) {
                        System.out.print(curArray.get(j).get(i) + " ");
                    }
                }
            }
            System.out.println();
        }
    }
}