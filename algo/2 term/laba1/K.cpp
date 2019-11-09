#include <iostream>
#include <algorithm>
using namespace std;
 
const int INF = static_cast<int>(1e5 + 1);
const int MAXN = static_cast<int>(1e5 + 1);
 
int t[4 * MAXN];
 
void build(int v, int vl, int vr, int a[]) {
    if (vl == vr) {
        t[v] = a[vl];
        return;
    }
    int vm = (vl + vr) / 2;
    build(2 * v + 1, vl, vm, a);
    build(2 * v + 2, vm + 1, vr, a);
    t[v] = min(t[2 * v + 1], t[2 * v + 2]);
}
 
int findMin(int v, int vl, int vr, int l, int r) {
    if (r < vl || vr < l) {
        return INF;
    }
    if (l <= vl && vr <= r) {
        return t[v];
    }
    int vm = (vl + vr) / 2;
    int min_left = findMin(2 * v + 1, vl, vm, l, r);
    int min_right = findMin(2 * v + 2, vm + 1, vr, l, r);
    return min(min_left, min_right);
}
 
void modifySet(int v, int vl, int vr, int pos, int val) {
    if (vl == vr) {
        t[v] = val;
        return;
    }
    int vm = (vl + vr) / 2;
    if (pos <= vm) {
        modifySet(2 * v + 1, vl, vm, pos, val);
    } else {
        modifySet(2 * v + 2, vm + 1, vr, pos, val);
    }
    t[v] = min(t[2 * v + 1], t[2 * v + 2]);
}
 
int main() {
  
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    freopen("parking.in", "r", stdin);
    freopen("parking.out", "w", stdout);
 
    string s;
    int n, m, x;
    cin >> n >> m;
 
    int a[MAXN];
    for (int i = 0; i < n; i++) {
        a[i] = i;
    }
    
    build(0, 0, n - 1, a);
 
    for (int i = 0; i < m; i++) {
        cin >> s >> x;
        if (s == "exit") {
            modifySet(0, 0, n - 1, x - 1, x - 1);
        }
        if (s == "enter") {
            int result = findMin(0, 0, n - 1, x - 1, n - 1);
            if (result == INF) {
                result = findMin(0, 0, n - 1, 0, x - 1);
            }
            modifySet(0, 0, n - 1, result, INF);
            cout << result + 1 << endl;
        }
    }
 
 
    return 0;
}