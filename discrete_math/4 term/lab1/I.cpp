#include <vector>
#include <iostream>
using namespace std;

const int MODULE = 104857601;

void check(int64_t &x) {
    while (x < 0) {
        x = (x + MODULE) % MODULE;
    }
}

int main() {

    int64_t k, n;
    cin >> k >> n;

    n -= 1;

    vector<int64_t> a(2 * k);
    vector<int64_t> q(k + 1);
    vector<int64_t> r(k + 1);
    vector<int64_t> negativeQ(k + 1);

    q[0] = 1;

    for (int i = 0; i < k; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= k; i++) {
        cin >> q[i];
        q[i] = (-q[i] + MODULE) % MODULE;
        check(q[i]);
    }

    while (n >= k) {
        for (int64_t i = k; i < 2 * k; i++) {
            int64_t sum = 0;
            for (int64_t j = 1; j <= k; j++) {
                sum = (sum - q[j] * a[i - j]) % MODULE;
                check(sum);
            }
            a[i] = sum;
        }
        for (int64_t i = 0; i <= k; i++) {
            negativeQ[i] = i % 2 == 0 ? q[i] : (-q[i] + MODULE) % MODULE;
            check(negativeQ[i]);
        }
        for (int64_t i = 0; i <= 2 * k; i += 2) {
            int64_t ithCoefficient = 0;
            for (int64_t j = 0; j <= i; j++) {
                int64_t coefficient = j > k ? 0 : q[j];
                int64_t negativeCoefficient = (i - j > k) ? 0 : negativeQ[i - j];
                ithCoefficient = (ithCoefficient + coefficient * negativeCoefficient + MODULE) % MODULE;
            }
            r[i / 2] = ithCoefficient;
        }
        for (int64_t i = 0; i <= k; i++) {
            q[i] = r[i];
        }
        int64_t filterCoefficient = 0;
        for (int64_t i = 0; i < 2 * k; i++) {
            if (n % 2 != i % 2) {
                continue;
            }
            a[filterCoefficient] = a[i];
            filterCoefficient++;
        }
        n /= 2;
    }

    cout << a[n] << endl;

    return 0;
}