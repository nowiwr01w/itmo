import java.util.List;
import java.util.ArrayList;
import java.io.InputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

class FastScanner {

    int maxLength = 0;
    private BufferedReader reader;

    FastScanner(InputStream stream) {
        reader = new BufferedReader(new InputStreamReader(stream));
    }

    String nextLine() throws IOException {
        return reader.readLine();
    }

    List<Integer> addArray(String curString) {
        List<Integer> resultList = new ArrayList<>();
        String[] tempList = curString.split("\\s");
        maxLength = Math.max(maxLength, tempList.length);
        for (String elem : tempList) {
            if (!elem.isEmpty()) {
                resultList.add(Integer.valueOf(elem));
            }
        }
        return resultList;
    }

    void close() throws IOException {
        reader.close();
    }
}