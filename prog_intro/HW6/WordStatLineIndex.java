import javafx.util.Pair;
import java.io.IOException;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

public class WordStatLineIndex {
    public static void main(String[] args) {

        if (args.length < 2) {
            System.out.println("Sosatt");
            System.exit(1);
        }

        List<List<String>> curPhrases = new ArrayList<>();
        Map<String, List<Pair<Integer, Integer>>> curMap = new TreeMap<>();

        try (FastScanner reader = new FastScanner(args[0])) {

            try {
                String tempString;
                while ((tempString = reader.nextLine()) != null) {
                    curPhrases.add(reader.addArray(tempString));
                }
                reader.close();
            } catch (IOException ex) {
                System.out.println(ex.getMessage());
            }

            for (int i = 0; i < curPhrases.size(); i++) {
                for (int j = 0; j < curPhrases.get(i).size(); j++) {
                    String curString = curPhrases.get(i).get(j);
                    List<Pair<Integer, Integer>> curPair = curMap.getOrDefault(curString, new ArrayList<>());
                        curPair.add(new Pair<>(i + 1, j + 1));
                        curMap.put(curString, curPair);
                }
            }
        } catch (IOException ex) {
            System.out.println(ex.getMessage());
        }

        try (PrintWriter printWriter = new PrintWriter(args[1], "UTF-8")){
            curMap.forEach((key, value) -> {
                printWriter.print(key + " " + value.size());
                for (Pair<Integer, Integer> curPair : value) {
                    printWriter.print(" " + curPair.getKey().toString() + ":" + curPair.getValue().toString());
                }
                printWriter.println();
            });
        } catch (IOException ex) {
            System.out.println(ex.getMessage());
        }
    }
}