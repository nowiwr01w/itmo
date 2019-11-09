#include <iostream>
#include <algorithm>
using namespace std;
 
int n;
int t[128][128][128];
 
long long sum(int x, int y, int z) {
    long long result = 0;
    for (int i = x; i >= 0; i = (i & (i + 1)) - 1) {
        for (int j = y; j >= 0; j = (j & (j + 1)) - 1) {
            for (int k = z; k >= 0; k = (k & (k + 1)) - 1) {
                result += t[i][j][k];
            }
        }
    }
    return result;
}
 
void inc(int x, int y, int z, int value) {
    for (int i = x; i < n; i = (i | (i + 1))) {
        for (int j = y; j < n; j = (j | (j + 1))) {
            for (int k = z; k < n; k = (k | (k + 1))) {
                t[i][j][k] += value;
            }
        }
    }
    return;
}
 
int main() {
    
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios_base::sync_with_stdio(false);
 
    cin >> n;
 
    int sym;
    int x, y, z, k;
    int x1, y1, z1, x2, y2, z2;
 
    long long result = 0;
 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k1 = 0; k1 < n; k1++) {
                t[i][j][k1] = 0;
            }
        }
    }
 
    while (cin >> sym) {
        if (sym == 1) {
            cin >> x >> y >> z >> k;
            inc(x, y, z, k);
        }
        if (sym == 2) {
            cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
            result = sum(x2, y2, z2) - sum(x1 - 1, y2, z2) - sum(x2, y1 - 1, z2) +
                     sum(x1 - 1, y1 - 1, z2) - sum(x2, y2, z1 - 1) + sum(x1 - 1, y2, z1 - 1) +
                     sum(x2, y1 - 1, z1 - 1) - sum(x1 - 1, y1 - 1, z1 - 1);
            cout << result << endl;
        }
        if (sym == 3) {
            break;
        }
    }
 
    return 0;
}