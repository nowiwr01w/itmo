#include <vector>
#include <iostream>
#include <algorithm>
 
using namespace std;
 
int main() {
 
    int t;
    long long int sum = 0;
    long long m, z, b_first;
    long long n, x, y, a_frrst;
 
    cin >> n >> x >> y >> a_frrst;
    cin >> m >> z >> t >> b_first;
 
    vector<long long> c(2 * m, 0);
    vector<long long> prefix(n + 1, 0);
 
    prefix[1] = a_frrst;
 
    long long b1 = b_first;
 
    for (int i = 2; i <= n; i++) {
        auto a_second = (x * a_frrst + y) % (1 << 16);
        prefix[i] = prefix[i - 1] + a_second;
        a_frrst = a_second;
    }
 
    for (int i = 0; i < 2 * m; i++) {
        b1 = (z * b_first + t + (1 << 30)) % (1 << 30);
        c[i] = b_first % n;
        b_first = b1;
    }
 
    for (int i = 0; i < 2 * m; i += 2) {
        auto min_ci = min(c[i], c[i + 1]);
        auto max_ci = max(c[i], c[i + 1]);
        if (min_ci < 1) {
            sum += prefix[min(n - 1, max_ci) + 1];
        } else {
            sum += prefix[min(n - 1, max_ci) + 1] - prefix[min_ci];
        }
    }
 
    cout << sum << endl;
 
    return 0;
}