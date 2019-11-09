#include <math.h>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

vector<vector<long long>> getCurVector(long long open) {
    vector<vector<long long>> cur_vec;
    for (int i = 0; i <= 2 * open; i++) {
        vector<long long> temp(open + 1);
        cur_vec.push_back(temp);
    }
    for (int i = 0; i <= 2 * open; i++) {
        for (int j = 0; j <= open; j++) {
            cur_vec[i][j] = 0;
        }
    }

    cur_vec[0][0] = 1;

    for (int i = 0; i < 2 * open; i++) {
        for (int j = 0; j <= open; j++) {
            if (j + 1 < open + 1) {
                cur_vec[i + 1][j + 1] += cur_vec[i][j];
            }
            if (j > 0) {
                cur_vec[i + 1][j - 1] += cur_vec[i][j];
            }
        }
    }
    return cur_vec;
}

long long brackets2num2(string cur_string, long long open) {

    vector<vector<long long>> cur_vec = getCurVector(open);

    vector<char> temp_vec;
    long long result_number = 0, balance = 0, dn = 2 * open;

    for (int i = 0; i < dn; i++) {
        if (cur_string[i] == '(') {
            temp_vec.push_back(cur_string[i]);
            balance += 1;
            continue;
        }

        long long depth = balance + 1;

        if (balance < open) {
            result_number += cur_vec[2 * open - i - 1][depth] * pow(2, ((2 * open - i - 1 - depth) / 2));
        }

        if (cur_string[i] == ')') {
            temp_vec.pop_back();
            balance -= 1;
            continue;
        }

        if (!temp_vec.empty() && temp_vec[temp_vec.size() - 1] == '(' && balance > 0) {
            depth = balance - 1;
            result_number += cur_vec[2 * open - i - 1][depth] * pow(2, ((2 * open - i - 1 - depth) / 2));
        }

        if (cur_string[i] == '[') {
            temp_vec.push_back(cur_string[i]);
            balance += 1;
            continue;
        }

        if (balance < open) {
            depth = balance + 1;
            result_number += cur_vec[2 * open - i - 1][depth] * pow(2, ((2 * open - i - 1 - depth) / 2));
        }

        if (cur_string[i] == ']') {
            temp_vec.pop_back();
            balance -= 1;
        }
    }
    return result_number;
}

int main() {

    cin.tie(0);
    ios_base::sync_with_stdio(0);

    freopen("brackets2num2.in", "r", stdin);
    freopen("brackets2num2.out", "w", stdout);

    string cur_string;
    long long open = 0;

    cin >> cur_string;

    for (char sym : cur_string) {
        if (sym == '(' || sym == '[')
            open += 1;
    }

    cout << brackets2num2(cur_string, open) << endl;

    return 0;
}