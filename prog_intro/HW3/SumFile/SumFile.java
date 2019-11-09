import javax.swing.text.StyledEditorKit;
import java.io.*;
import java.util.*;

// Chtck SumHexFile
public class SumFile {
    public static void main(String[] args) throws IOException {

        int sum = 0;
        InputStreamReader inputStr = new InputStreamReader(new FileInputStream(args[0]), "utf-8");
        Scanner inString = new Scanner(inputStr);
        try {
            for (String curStr : inputStr.toString().split("\\p{javaWhitespace}+")) {
                if (!curStr.isEmpty()) {
                    sum += Integer.parseInt(curStr);
                }
            }
        } catch (FileNotFoundException e) {
            System.out.println(e.getMessage());
        } catch (UnsupportedEncodingException e) {
            System.out.println(e.getMessage());
        } finally {
            inString.close();
        }

        try {
            OutputStreamWriter outString = new OutputStreamWriter(new FileOutputStream(args[1]), "utf-8");
            try {
                outString.write(sum + "");
            } catch (IOException e) {
                System.out.println(e.getMessage());
            } finally {
                outString.close();
            }
        } catch (FileNotFoundException e) {
            System.out.println(e.getMessage());
        } catch (UnsupportedEncodingException e) {
            System.out.println(e.getMessage());
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }
}