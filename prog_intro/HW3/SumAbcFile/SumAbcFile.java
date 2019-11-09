import java.util.*;
import java.io.*;

// Chtck SumHexFile
public class SumAbcFile {
    public static void main(String[] args) {

        int resultSum = 0;
        // InputStreamReader can convert current file/array of byte/other threads to string (thread of symbols)
        try (InputStreamReader inputStr = new InputStreamReader(new FileInputStream(args[0]), "utf-8")) {
            Scanner inString = new Scanner(inputStr);
            while (inString.hasNext()) {
                String currentString = inString.next();
                StringBuilder number = new StringBuilder();
                for (int i = 0; i < currentString.length(); i++) {
                    char currentSymbol = currentString.charAt(i);
                    if (Character.isLetter(currentSymbol)) {
                        currentSymbol = Character.toLowerCase(currentSymbol);
                        currentSymbol -= 'a';
                        // Check ASCII
                        currentSymbol += '0';
                    }
                    number.append(currentSymbol);
                }
                resultSum += Integer.parseInt(number.toString());
            }
        } catch (FileNotFoundException e) {
            System.out.println(e.getMessage());
        } catch (UnsupportedEncodingException e) {
            System.out.println(e.getMessage());
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }

        // Trying to write the answer
        try (OutputStreamWriter outString = new OutputStreamWriter(new FileOutputStream(args[1]), "utf-8")) {
            outString.write(resultSum + "");
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }
}