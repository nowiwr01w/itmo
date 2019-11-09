import java.io.*;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class SumHexFile {
    public static void main(String[] args) {

        if (args.length < 2) {
            System.exit(1);
        }

        int resultSumHex = 0;

        // 0 или 1 "-" (HEX | DEC)
        Pattern pattern = Pattern.compile("-?((0[xX][0-9a-fA-F]+)|([0-9]+))");

        // InputStreamReader can convert current file/array of byte/other threads to string (thread of symbols)
        try (InputStreamReader inputStr = new InputStreamReader(new FileInputStream(args[0]))) {
            Scanner inString = new Scanner(inputStr);
            while (inString.hasNextLine()) {
                Matcher goodPattern = pattern.matcher(inString.nextLine());
                while (goodPattern.find()) {
                    if (goodPattern.group(2) != null) {
                        resultSumHex += Long.decode(goodPattern.group());
                    } else {
                        resultSumHex += Long.parseLong(goodPattern.group());
                    }
                }
            }
        } catch (FileNotFoundException e) {
            System.out.println(e.getMessage());
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }

        // Trying to write the answer
        try (OutputStreamWriter outString = new OutputStreamWriter(new FileOutputStream(args[1]))) {
            outString.write(resultSumHex + "");
        } catch (FileNotFoundException e) {
            System.out.println(e.getMessage());
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }
}