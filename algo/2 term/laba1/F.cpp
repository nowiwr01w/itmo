#include <iostream>
using namespace std;
 
const int MAXN = 2 * 100000;
 
long long a[MAXN];
long long logs[MAXN];
long long sparseTable[MAXN][25];
 
void createSparseTable(int n) {
    for (int i = 1; i <= n; i++) {
        sparseTable[i][0] = a[i];
    }
    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 1; i <= n; i++) {
            sparseTable[i][j] = min(sparseTable[i][j - 1], sparseTable[i + (1 << (j - 1))][j - 1]);
        }
    }
}
 
long long getLog(int cur_number) {
    if (cur_number == 1) {
        return 0;
    }
    return getLog(cur_number / 2) + 1;
}
 
long long getMinValue(long long left, long long right) {
    long long curLog = logs[right - left + 1];
    return min(sparseTable[left][curLog], sparseTable[right - (1 << (curLog)) + 1][curLog]);
}
 
int main() {
 
    int n, m;
    long long left, right;
 
    cin >> n >> m >> a[1];
    cin >> left >> right;
 
    for (int i = 2; i <= n; i++) {
        a[i] = (a[i - 1] * 23 + 21563) % 16714589;
    }
 
    for (int i = 1; i <= n + 1; i++) {
        logs[i] = getLog(i);
    }
 
    createSparseTable(n);
 
    long long new_left = min(left, right);
    long long new_right = max(left, right);
    long long answer = getMinValue(new_left, new_right);
 
    for (int i = 1; i < m; i++) {
        left = ((17 * left + 751 + answer + 2 * i) % n) + 1;
        right = ((13 * right + 593 + answer + 5 * i) % n) + 1;
        new_left = min(left, right);
        new_right = max(left, right);
        answer = getMinValue(new_left, new_right);
    }
 
    cout << left << " " << right << " " << answer << endl;
 
    return 0;
}