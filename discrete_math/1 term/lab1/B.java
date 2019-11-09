import java.util.Scanner;
 
public class hornForm {
 
    static int variables;
    static int clerks;
 
    static boolean isEmptyDis(int[][] mas, int row) {
        int count = 0;
        for (int i = 0; i < variables; i++) {
            if (mas[row][i] == -1) {
                count += 1;
            }
        }
        return (count == variables - 1);
    }
 
    static void deleteDis(int[][] mas, int row) {
        for (int i = row; i < clerks - 1; i++) {
            for (int j = 0; j < variables; j++) {
                mas[i][j] = mas[i + 1][j];
            }
        }
    }
 
    public static void main(String[] args) {
 
        Scanner scanner = new Scanner(System.in);
 
        variables = scanner.nextInt();
        clerks = scanner.nextInt();
 
        int[][] elements = new int[clerks][variables];
 
        for (int i = 0; i < clerks; i++) {
            for (int j = 0; j < variables; j++) {
                elements[i][j] = scanner.nextInt();
            }
        }
 
        int curDis = 0;
        boolean exitDeadLine = false;
 
        do {
            if (isEmptyDis(elements, curDis)) {
                int emptyVarNum;
                for (emptyVarNum = 0; emptyVarNum < variables; emptyVarNum++) {
                    if (elements[curDis][emptyVarNum] != -1) {
                        break;
                    }
                }
 
                int emptyDisVal = elements[curDis][emptyVarNum];
 
                for (int i = 0; i < clerks; i++) {
                    if (elements[i][emptyVarNum] == emptyDisVal) {
                        deleteDis(elements, i);
                        clerks -= 1;
                        i -= 1;
                    } else if (elements[i][emptyVarNum] != -1) {
                        if (isEmptyDis(elements, i)) {
                            exitDeadLine = true;
                        } else {
                            elements[i][emptyVarNum] = -1;
                        }
                    }
                }
                curDis = -1;
            }
            if (exitDeadLine) {
                break;
            }
            curDis += 1;
        } while (curDis < clerks);
 
        if (exitDeadLine) {
            System.out.println("YES");
        }
        else {
            System.out.println("NO");
        }
    }
}