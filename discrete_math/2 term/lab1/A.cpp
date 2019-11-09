#include <iostream>
using namespace std;

int main() {

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    freopen("exam.in", "r", stdin);
    freopen("exam.out", "w", stdout);

    int k, n;
    double a, b;
    cin >> k >> n;

    double result = 0;
    for (int i = 0; i < k; i++) {
        cin >> a >> b;
        result += (a / n) * (b / 100);
    }

    cout.precision(5);
    cout << result << endl;

    return 0;
}