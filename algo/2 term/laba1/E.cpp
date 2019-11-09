#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
 
#define MAXN 200000
 
struct Matrix {
    long long a = 1, b = 0;
    long long c = 0, d = 1;
 
    void getFromCin() {
        cin >> a >> b >> c >> d;
    }
 
    void printToCout() {
        cout << a << ' ' << b << '\n' << c << ' ' << d << "\n" << "\n";
    }
};
 
Matrix neutral;
Matrix a[MAXN];
Matrix t[4 * MAXN];
 
int pr;
 
Matrix operator*(Matrix a, Matrix b) {
    Matrix ans;
    ans.a = ((a.a * b.a) + (a.b * b.c)) % pr;
    ans.b = ((a.a * b.b) + (a.b * b.d)) % pr;
    ans.c = ((a.c * b.a) + (a.d * b.c)) % pr;
    ans.d = ((a.c * b.b) + (a.d * b.d)) % pr;
    return ans;
}
 
void build(int v, int vl, int vr, Matrix a[]) {
    if (vl == vr) {
        t[v] = a[vl];
        return;
    }
    int vm = (vr + vl) / 2;
    build(2 * v + 1, vl, vm, a);
    build(2 * v + 2, vm + 1, vr, a);
    t[v] = t[2 * v + 1] * t[2 * v + 2];
}
 
Matrix get(int v, int vl, int vr, int l, int r) {
    if (r < vl || vr < l) {
        return neutral;
    }
    if (vl >= l && vr <= r) {
        return t[v];
    }
    int vm = (vr + vl) / 2;
    Matrix left = get(2 * v + 1, vl, vm, l, r);
    Matrix right = get(2 * v + 2, vm + 1, vr, l, r);
    return left * right;
}
 
int main() {
 
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios::sync_with_stdio(false);
    freopen("crypto.in", "r", stdin);
    freopen("crypto.out", "w", stdout);
 
    int n, m, l, r;
    cin >> pr >> n >> m;
 
    for (int i = 0; i < n; i++) {
        a[i].getFromCin();
    }
 
    build(0, 0, n - 1, a);
 
    for (int i = 0; i < m; i++) {
        cin >> l >> r;
        get(0, 0, n - 1, l - 1, r - 1).printToCout();
    }
 
    return 0;
}