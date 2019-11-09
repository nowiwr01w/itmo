import java.util.List;
import java.util.Scanner;
import java.util.ArrayList;

public class B {
    private static int remove(List<Integer> curList, int startCount) {
        for (int i = 2; i < startCount; i++) {
            if (curList.get(i - 1).equals(curList.get(i)) && curList.get(i - 2).equals(curList.get(i - 1))) {
                int result = 0;
                int index = i - 2;
                int ball = curList.get(i);
                while (index < startCount && curList.get(index) == ball) {
                    result += 1;
                    startCount -= 1;
                    curList.remove(index);
                }
                return result;
            }
        }
        return 0;
    }

    public static void main(String[] args) {

        Scanner scan = new Scanner(System.in);
        int startCount = scan.nextInt();

        List<Integer> curList = new ArrayList<>();

        for (int i = 0; i < startCount; i++) {
            curList.add(scan.nextInt());
        }

        int count = 0;
        int curResult = remove(curList, startCount);

        while (curResult > 0) {
            count += curResult;
            startCount -= curResult;
            curResult = remove(curList, startCount);
        }

        System.out.println(count);
    }

}