#include <cmath>
#include <iostream>
using namespace std;

int main() {

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    freopen("shooter.in", "r", stdin);
    freopen("shooter.out", "w", stdout);

    int n, m, k;
    double result_up = 0;
    double result_down = 0;

    cin >> n >> m >> k;

    double pi;
    for (int i = 0; i < n; i++) {
        cin >> pi;
        if (i == k - 1) {
            result_up = pow(1 - pi, m);
        }
        result_down += pow(1 - pi, m);
    }

    cout.precision(13);
    cout << result_up / result_down << endl;

    return 0;
}