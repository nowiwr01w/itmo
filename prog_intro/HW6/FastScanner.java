import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;
import java.util.List;
import java.util.ArrayList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

class FastScanner implements AutoCloseable {

    private BufferedReader reader;

    FastScanner(String stream) throws IOException {
        reader = new BufferedReader(new InputStreamReader(new FileInputStream(stream), StandardCharsets.UTF_8));
    }

    String nextLine() throws IOException {
        return reader.readLine();
    }

    List<String> addArray(String curString) {
        List<String> resultList = new ArrayList<>();
        Matcher matcher = Pattern.compile("[\\p{L}\\p{Pd}\\']+").matcher(curString);
        while (matcher.find()) {
            String goodPattern = matcher.group();
            if (!goodPattern.isEmpty()) {
                resultList.add(goodPattern.toLowerCase());
            }
        }
        return resultList;
    }

    @Override
    public void close() throws IOException {
        reader.close();
    }
}