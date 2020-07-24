#include <vector>
#include <iostream>
using namespace std;

const int MODULE = 1000000007;

int main() {

    int64_t x;
    int64_t k, m;
    cin >> k >> m;

    vector<int64_t> tree(m + 1, 0);
    vector<int64_t> result(m + 1, 0);
    vector<int64_t> prefixSums(m + 1, 0);

    result[0] = 1;
    prefixSums[0] = 1;

    for (int64_t i = 0; i < k; i++) {
        cin >> x;
        tree[x] = 1;
    }

    for (int64_t i = 1; i <= m; i++) {
        int64_t sum = 0;
        for (int64_t j = 0; j <= i; j++) {
            if (tree[j] == 0) {
                continue;
            }
            sum += prefixSums[i - j] % MODULE;
        }
        result[i] = sum % MODULE;
        for (int64_t j = 0; j <= i; j++) {
            prefixSums[i] = (prefixSums[i] + result[j] * result[i - j]) % MODULE;
        }
        cout << result[i] << " ";
    }

    return 0;
}