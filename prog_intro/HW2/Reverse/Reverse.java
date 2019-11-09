import java.util.*;
import java.lang.*;
import java.io.*;

public class Reverse {
    public static void main(String[] args) {

    Scanner in = new Scanner(System.in);
    ArrayList <String> cur_array = new ArrayList <String>();
 
    while (in.hasNextLine()) {
        cur_array.add(in.nextLine());
    }

    Collections.reverse(cur_array);
    
    for (String cur_str : cur_array) {
        String[] temp_array = cur_str.split("\\p{javaWhitespace}+");
        Collections.reverse(Arrays.asList(temp_array));
        for (String sub_str : temp_array) {
            System.out.print(sub_str + " ");
	}
        System.out.println();
    }
  }
}