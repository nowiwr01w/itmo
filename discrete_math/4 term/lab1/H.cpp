#include <cmath>
#include <vector>
#include <iostream>
using namespace std;

const int MODULE = 998244353;

int64_t get(const vector<int64_t> &vector, const int index) {
    return index < vector.size() ? vector[index] : 0;
}

int64_t even(const int64_t &index) {
    return index % 2 == 0 ? 1 : -1;
}

void check(int64_t &x) {
    while (x < 0) {
        x = (x + MODULE) % MODULE;
    }
}

int main() {

    int64_t k, n;
    cin >> k >> n;

    auto double_k = static_cast<double>(k);

    auto first = ceil((double_k - 1) / 2);
    auto second = ceil(double_k / 2);

    vector<int64_t> p(first);
    vector<int64_t> q(second);
    vector<int64_t> coefficient(n + 1, 0);
    vector<vector<int64_t>> coeff(k + 1, vector<int64_t>(k + 1, 0));

    for (int64_t i = 0; i <= k; i++) {
        coeff[i][0] = coeff[i][i] = 1;
        for (int64_t j = 1; j < i; j++) {
            coeff[i][j] = (coeff[i - 1][j - 1] + coeff[i - 1][j]) % MODULE;
        }
    }

    for (int64_t i = 0; i < p.size(); i++) {
        p[i] = coeff[k - i - 2][i] * even(i);
    }
    for (int64_t i = 0; i < q.size(); i++) {
        q[i] = coeff[k - i - 1][i] * even(i);
    }

    for (int64_t i = 0; i < n; i++) {
        int64_t cur = get(p, i);
        for (int64_t j = 0; j <= i; j++) {
            cur = (cur - (coefficient[i - j] * get(q, j)) % MODULE + MODULE) % MODULE;
        }
        check(cur);
        coefficient[i] = cur;
        cout << coefficient[i] << endl;
    }

    return 0;
}