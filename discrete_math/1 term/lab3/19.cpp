#include <math.h>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

vector<vector<long long>> getCurVector(long long n) {
    vector<vector<long long>> cur_vec;
    for (int i = 0; i < n * 2 + 1; i++) {
        vector<long long> temp(n + 1);
        cur_vec.push_back(temp);
    }

    for (int i = 0; i < 2 * n + 1; i++) {
        for (int j = 0; j < n + 1; j++) {
            cur_vec[i][j] = 0;
        }
    }

    cur_vec[0][0] = 1;

    for (int i = 0; i < n * 2; i++) {
        for (int j = 0; j < n + 1; j++) {
            if (j + 1 < n + 1) {
                cur_vec[i + 1][j + 1] += cur_vec[i][j];
            }
            if (j > 0) {
                cur_vec[i + 1][j - 1] += cur_vec[i][j];
            }
        }
    }
    return cur_vec;
}

string getSolution(long long n, long long k) {
    k += 1;
    vector<vector<long long>> dp = getCurVector(n);

    string cur_str = "";
    long long depth = 0;
    vector<char> cur_stack(2 * n);

    for (long long i = n * 2 - 1; i != -1; i--) {
        long long temp;
        if (depth + 1 < n + 1)
            temp = dp[i][depth + 1] << ((i - depth - 1) / 2);
        else {
            temp = 0;
        }
        if (temp >= k) {
            cur_str += '(';
            cur_stack.push_back('(');
            depth++;
            continue;
        }

        k -= temp;

        if (!cur_stack.empty() && cur_stack[cur_stack.size() - 1] == '(' && depth > -1) {
            temp = dp[i][depth - 1] << ((i - depth + 1) / 2);
        } else {
            temp = 0;
        }

        if (temp >= k) {
            cur_str += ')';
            cur_stack.pop_back();
            depth -= 1;
            continue;
        }

        k -= temp;

        if (depth + 1 < n + 1) {
            temp = dp[i][depth + 1] << ((i - depth - 1) / 2);
        } else {
            temp = 0;
        }
        if (temp >= k) {
            cur_str += '[';
            cur_stack.push_back('[');
            depth += 1;
            continue;
        }
        k -= temp;
        cur_str += ']';
        cur_stack.pop_back();
        depth -= 1;
    }
    return cur_str;
}

int main() {

    cin.tie(0);
    ios_base::sync_with_stdio(0);

    freopen("num2brackets2.in", "r", stdin);
    freopen("num2brackets2.out", "w", stdout);

    long long n, k;
    cin >> n >> k;

    string s = getSolution(n, k);
    cout << s << endl;

    return 0;
}

