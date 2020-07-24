#include <vector>
#include <iostream>
using namespace std;

int64_t N = 7;
int64_t index = 0;

string input;
vector<int64_t > result;

int64_t fact(int64_t left, int64_t right) {
    int64_t fact = 1;
    for (int64_t i = left + 1; i <= right; i++) {
        fact *= i;
    }
    return fact;
}

vector<int64_t > parser() {
    vector<int64_t > first;
    vector<int64_t > weights(N);
    if (input[index] == 'B') {
        weights[1] = 1;
    }
    else if (input[index] == 'L') {
        index += 2;
        first = parser();
        weights[0] = 1;
        for (int64_t i = 1; i < N; i++) {
            for (int64_t j = 1; j <= i; j++) {
                weights[i] += first[j] * weights[i - j];
            }
        }
    }
    else if (input[index] == 'P') {
        index += 2;
        first = parser();
        index += 1;
        vector<int64_t > second = parser();
        for (int64_t i = 0; i < N; i++) {
            for (int64_t j = 0; j <= i; j++) {
                weights[i] += first[j] * second[i - j];
            }
        }
    }
    else if (input[index] == 'S') {
        index += 2;
        first = parser();
        vector<vector<int64_t >> dp(N, vector<int64_t >(N));
        dp[0] = vector<int64_t >(N, 1);
        dp[0][0] = weights[0] = 1;
        for (int64_t i = 1; i < N; i++) {
            for (int64_t j = 1; j < N; j++) {
                for (int64_t k = 0; k <= i / j; k++) {
                    int64_t max1 = max(0LL, first[j] + k - 1);
                    int64_t coeff = fact(max1 - k, max1) / fact(1, k);
                    dp[i][j] += coeff * dp[i - k * j][j - 1];
                }
            }
            weights[i] = dp[i][i];
        }
    }
    index += 1;
    return weights;
}

int main() {

    cin >> input;
    result = parser();

    for (int64_t i = 0; i < N; i++) {
        cout << result[i] << " ";
    }

    return 0;
}