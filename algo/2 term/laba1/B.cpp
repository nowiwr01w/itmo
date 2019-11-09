#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
 
long long t[4 * 500000];
#define INF 10000 * 10000 + 2;
 
void buildSum(long long v, long long vl, long long vr, long long a[]) {
    if (vl == vr) {
        t[v] = a[vl];
        return;
    }
    long long vm = vl + (vr - vl) / 2;
    buildSum(2 * v + 1, vl, vm, a);
    buildSum(2 * v + 2, vm + 1, vr, a);
    t[v] = t[2 * v + 1] + t[2 * v + 2];
}
 
long long querySum(long long v, long long vl, long long vr, long long l, long long r) {
    if (r < vl || vr < l) {
        return 0;
    }
    if (vl >= l && vr <= r) {
        return t[v];
    }
    long long vm = vl + (vr - vl) / 2;
    long long ql = querySum(2 * v + 1, vl, vm, l, r);
    long long qr = querySum(2 * v + 2, vm + 1, vr, l, r);
    return ql + qr;
}
 
// �������� �� ������� pos ��������� �������� value
void modify(long long v, long long vl, long long vr, long long pos, long long value) {
    if (vl == vr) {
        t[v] = value;
        return;
    }
    long long vm = vl + (vr - vl) / 2;
    if (pos <= vm) {
        modify(2 * v + 1, vl, vm, pos, value);
    } else {
        modify(2 * v + 2, vm + 1, vr, pos, value);
    }
    t[v] = t[2 * v + 1] + t[2 * v + 2];
}
 
int main() {
 
    cin.tie(0);
    ios_base::sync_with_stdio(0);
 
 
    string query;
    long long a[500000];
    long long aSize, l, r;
 
    cin >> aSize;
 
    for (long long i = 0; i < aSize; i++) {
        cin >> a[i];
    }
 
    buildSum(0, 0, aSize - 1, a);
 
    while (cin >> query) {
        if (query == "sum") {
            cin >> l >> r;
            cout << querySum(0, 0, aSize - 1, l - 1, r - 1) << endl;
        }
        if (query == "set") {
            long long pos, val;
            cin >> pos >> val;
            modify(0, 0, aSize - 1, pos - 1, val);
        }
    }
 
    return 0;
}