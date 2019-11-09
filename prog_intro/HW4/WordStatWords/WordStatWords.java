import java.util.*;
import java.lang.*;
import java.io.*;
import java.util.regex.*;

public class WordStatWords {
    public static void main(String[] args) {
        try {
            String inputFileString = "";
            Map<String, Integer> curMap = new TreeMap<>();
            BufferedReader reader = new BufferedReader(new InputStreamReader(new FileInputStream(args[0]), "UTF-8"));
            try {
                String tempLine;
                while ((tempLine = reader.readLine()) != null) {
                    inputFileString += tempLine + " ";
                }

                // p{L} - any letters, p{Pd} - знаки препинания и тире
                Matcher matcher = Pattern.compile("[\\p{L}\\p{Pd}\\']+").matcher(inputFileString);

                while (matcher.find()) {
                    String goodPattern = matcher.group();
                    if (goodPattern.length() > 0) {
                        goodPattern = goodPattern.toLowerCase();
                        if (curMap.containsKey(goodPattern)) {
                            curMap.put(goodPattern, curMap.get(goodPattern) + 1);
                        } else {
                            curMap.put(goodPattern, 1);
                        }
                    }
                }
                reader.close();
            } catch (InputMismatchException ex) {
                System.out.println("InputMismatchException");
                System.exit(1);
            } catch (IOException ex) {
                System.out.println("Something went wrong while writing the result number");
                System.exit(1);
            }
            try {
                PrintWriter out = new PrintWriter(args[1], "UTF-8");
                for (Map.Entry<String, Integer> entry : curMap.entrySet()) {
                    out.println(entry.getKey() + " " + entry.getValue());
                }
                out.close();
            } catch (IOException ex) {
                System.out.println("Something went wrong while writing the result number");
                System.exit(1);
            }

        } catch (FileNotFoundException ex) {
            System.out.println("File " + args[0] + " not found");
            System.exit(1);
        }
        catch (UnsupportedEncodingException ex) {
            System.out.println("UnsupportedEncodingException");
            System.exit(1);
        }
    }
}