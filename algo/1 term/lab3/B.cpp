#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m;
    cin >> n >> m;
    vector<char> result;
    vector<vector<int>> cur(n, vector<int>(m, 1));
    vector<vector<int>> count(n, vector<int>(m, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> cur[i][j];
        }
    }

    count[0][0] = cur[0][0];
    for (int i = 1; i < m; i++) {
        count[0][i] = count[0][i - 1] + cur[0][i];
    }

    for (int i = 1; i < n; i++) {
        count[i][0] = count[i - 1][0] + cur[i][0];
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            if (count[i][j - 1] >= count[i - 1][j]) {
                //result.push_back('R');
                count[i][j] = cur[i][j] + count[i][j - 1];
            } else {
                //result.push_back('D');
                count[i][j] = cur[i][j] + count[i - 1][j];
            }
        }
    }

    int i = n - 1;
    int j = m - 1;
    while (i > 0 && j > 0) {
        if (count[i][j - 1] > count[i - 1][j]) {
            result.push_back('R');
            j = j - 1;
        } else {
            result.push_back('D');
            i = i - 1;
        }
    }
    while (i > 0) {
        result.push_back('D');
        i -= 1;
    }
    while (j > 0) {
        result.push_back('R');
        j -= 1;
    }

    cout << count[n - 1][m - 1] << endl;

    for (int t = result.size() - 1; t >= 0; t--) {
        cout << result[t];
    }

    return 0;
}