import java.util.List;
import java.util.Scanner;
import java.util.ArrayList;

public class Main {
    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt();
        if (n == 0) {
            System.out.println(0 + "\n" + 0 + " " + 0);
            return;
        }

        int[] price = new int[n];
        int[][] prev = new int[n][n + 2];
        int[][] money = new int[n][n + 2];

        for (int i = 0; i < n; i++) {
            price[i] = sc.nextInt();
            money[i][0] = Integer.MAX_VALUE / 2;
        }

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n + 2; j++) {
                money[i][j] = Integer.MAX_VALUE / 2;
            }
        }

        if (price[0] > 100) {
            money[0][2] = price[0];
        } else {
            money[0][1] = price[0];
        }

        for (int i = 1; i < n; i++) {
            for (int j = 1; j < i + 2; j++) {
                if (price[i] > 100) {
                    if (j == i + 1) {
                        money[i][j + 1] = money[i - 1][j] + price[i];
                        prev[i][j + 1] = j;
                    }
                    if (money[i - 1][j - 1] + price[i] <= money[i - 1][j + 1]) {
                        money[i][j] = money[i - 1][j - 1] + price[i];
                        prev[i][j] = j - 1;
                    } else {
                        money[i][j] = money[i - 1][j + 1];
                        prev[i][j] = j + 1;
                    }
                } else {
                    if (money[i - 1][j] + price[i] <= money[i - 1][j + 1]) {
                        money[i][j] = money[i - 1][j] + price[i];
                        prev[i][j] = j;
                    } else {
                        money[i][j] = money[i - 1][j + 1];
                        prev[i][j] = j + 1;
                    }
                }
            }
        }

        int answer = money[n - 1][1], lastPosition = 1, used = 0;
        for (int i = 1; i < n + 2; i++) {
            if (money[n - 1][i] <= answer) {
                answer = money[n - 1][i];
                lastPosition = i;
            }
        }
        
        List<Integer> result = new ArrayList<>();
        int i = n - 1, curLastPosition = lastPosition;
        
        while (i > 0) {
            if (prev[i][curLastPosition] > curLastPosition) {
                used += 1;
                result.add(i + 1);
            }
            curLastPosition = prev[i][curLastPosition];
            i -= 1;
        }
        lastPosition -= 1;
        
        System.out.println(answer);
        System.out.println(lastPosition + " " + used);
        for (int ind = result.size() - 1; ind >= 0; ind--) {
            System.out.println(result.get(ind));
        }
    }
}