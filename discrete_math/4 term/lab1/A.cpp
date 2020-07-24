#include <vector>
#include <iostream>
using namespace std;

const int MODULE = 998244353;

uint64_t getElement(const vector<uint64_t>& pol, const int index) {
    return index >= pol.size() ? 0 : pol[index];
}

int main() {

    int n, m;
    cin >> n >> m;

    vector<uint64_t> first(n + 1);
    vector<uint64_t> second(m + 1);
    vector<uint64_t> coeff(1000, 0);
    vector<uint64_t> product(n + m + 1, 0);

    for (int i = 0; i <= n; i++) {
        cin >> first[i];
    }
    for (int i = 0; i <= m; i++) {
        cin >> second[i];
    }

    cout << max(m, n) << endl;

    for (int i = 0; i <= max(m, n); i++) {
        uint64_t cur = getElement(first, i) + getElement(second, i);
        cout << cur % MODULE << ' ';
    }

    cout << endl << n + m << endl;

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            uint64_t cur = getElement(first, i) * getElement(second, j);
            product[i + j] = (product[i + j] + cur) % MODULE;
        }
    }
    for (uint64_t i : product) {
        cout << i << ' ';
    }

    cout << endl;

    for (int i = 0; i < 1000; i++) {
        uint64_t current = getElement(first, i);
        for (int j = 1; j <= m; j++) {
            if (j > i) {
                break;
            }
            current = (current - (coeff[i - j] * getElement(second, j)) % MODULE + MODULE) % MODULE;
        }
        coeff[i] = current;
        cout << coeff[i] << ' ';
    }

    return 0;
}