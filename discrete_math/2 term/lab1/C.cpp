#include <iostream>
using namespace std;

int main() {

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    freopen("lottery.in", "r", stdin);
    freopen("lottery.out", "w", stdout);

    int n, m;
    double cur;
    double result = 0;

    cin >> n >> m;

    int a[m], b[m];

    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i];
    }

    cur = 1.0 / a[0];
    for (int i = 1; i < m; i++) {
        result += cur * b[i - 1] * (a[i] - 1.0) / a[i];
        cur /= a[i];
    }

    result += b[m - 1] * cur;
    
    cout.precision(5);
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);

    cout << n - result << endl;

    return 0;
}