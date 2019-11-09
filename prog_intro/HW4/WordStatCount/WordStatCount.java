import java.util.*;
import java.lang.*;
import java.io.*;
import java.util.regex.*;

// WordStatWords.java - исправлено бросание IOException и некоторые синтаксические правки
public class WordStatCount {
    public static void main(String[] args) throws IOException {
        try {
            String inputFileString = "";
            Map<String, Integer> curMap = new LinkedHashMap<String, Integer>();
            BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream(args[0]), "UTF-8"));
            try {
                String tempLine;
                while ((tempLine = reader.readLine()) != null) {
                    inputFileString += tempLine + " ";
                }

                // p{L} - any letters, p{Pd} - знаки препинания и тире
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

            } catch (InputMismatchException ex) {
                System.out.println("InputMismatchException");
                System.exit(1);
            } catch (IllegalStateException ex) {
                System.out.println("IllegalStateException");
                System.exit(1);
            } finally {
                reader.close();
                try {
                    PrintWriter out = new PrintWriter(args[1], "UTF-8");
                    curMap.entrySet().stream().sorted(Map.Entry.comparingByValue()).
                            forEach(entry -> out.println(entry.getKey() + " " + entry.getValue()));
                    out.close();
                } catch (IOException ex) {
                    System.out.println("Something went wrong while writing the result number");
                    System.exit(1);
                }
            }
        } catch (FileNotFoundException ex) {
            System.out.println("File " + args[0] + " not found");
            System.exit(1);
        }
    }
}