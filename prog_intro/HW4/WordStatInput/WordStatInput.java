import java.util.*;
import java.lang.*;
import java.io.*;
import java.util.regex.*;

// WordStatWords.java - исправлено бросание IOException и некоторые синтаксические правки
public class WordStatInput {
    public static void main(String[] args) throws IOException {

        String inputFileString = "";
        BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream(args[0]), "UTF-8"));

        try {
            String tempLine;
            while ((tempLine = reader.readLine()) != null) {
                inputFileString += tempLine + " ";
            }
        } catch (FileNotFoundException | UnsupportedEncodingException | InputMismatchException e) {
            System.err.println("I feel sorry");
        } finally {
            reader.close();
        }

        // p{L} - any letters, p{Pd} - знаки препинания и тире
        Map<String, Integer> curMap = new LinkedHashMap<String, Integer>();
        Pattern pattern = Pattern.compile("[\\p{L}\\p{Pd}\\']+");
        Matcher matcher = pattern.matcher(inputFileString);

        while (matcher.find()) {
            String goodPattern = matcher.group();
            if (goodPattern.length() > 0) {
                goodPattern = goodPattern.toLowerCase();
                if (curMap.containsKey(goodPattern))
                    curMap.put(goodPattern, curMap.get(goodPattern) + 1);
                else
                    curMap.put(goodPattern, 1);
            }
        }

        PrintWriter out = new PrintWriter(args[1], "UTF-8");
        for (Map.Entry<String, Integer> entry : curMap.entrySet()) {
            out.println(entry.getKey() + " " + entry.getValue());
        }
        out.close();
    }
}