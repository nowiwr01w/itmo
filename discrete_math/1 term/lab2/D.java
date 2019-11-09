import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.*;
 
public class Main {
    public static void main(String[] args) throws IOException {
 
        Scanner scan = new Scanner(new File("lzw.in"));
        PrintWriter pw = new PrintWriter(new File("lzw.out"));
 
        String inputStr = scan.nextLine();
        List<Integer> curList = getLwzCodes(inputStr);
 
        for (Integer aCurList : curList) {
            pw.write(aCurList + " ");
        }
 
        scan.close();
        pw.close();
    }
 
 
    public static List<Integer> getLwzCodes(String initString) {
 
        int capacity = 26;
        Map<String, Integer> dictionary = new HashMap<>();
 
        for (int i = 97; i < 123; i++) {
            dictionary.put("" + (char)i, i - 97);
        }
 
        String curStr = "";
        List<Integer> result = new ArrayList<>();
 
        for (char symbol : initString.toCharArray()) {
            String change = curStr + symbol;
            if (dictionary.containsKey(change)) {
                curStr = change;
            } else {
                result.add(dictionary.get(curStr));
                dictionary.put(change, capacity);
                curStr = "" + symbol;
                capacity += 1;
            }
        }
 
        if (!curStr.equals("")) {
            result.add(dictionary.get(curStr));
        }
 
        return result;
    }
}