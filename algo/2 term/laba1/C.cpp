#include <vector>
#include <string>
#include <iostream>
using namespace std;
 
const int MAXN = static_cast<const int>(1e6);
const long long INF = static_cast<const long long>(1e18);
 
long long a[MAXN];
long long t[4 * MAXN];
long long setted[4 * MAXN];
long long added[4 * MAXN];
 
long long min(long long first, long long second) {
    if (first < second) {
        return first;
    }
    return second;
}
 
void build(long long v, long long tl, long long tr) {
    setted[v] = INF;
    if (tl == tr) {
        t[v] = a[tl];
        return;
    }
    long long tm = tl + (tr - tl) / 2;
    build(2 * v + 1, tl, tm);
    build(2 * v + 2, tm + 1, tr);
    t[v] = min(t[2 * v + 1], t[2 * v + 2]);
}
 
void push(long long v, long long tl, long long tr) {
    if (setted[v] != INF) {
        t[v] = setted[v];
        if (tl != tr) {
            added[2 * v + 1] = 0;
            added[2 * v + 2] = 0;
            setted[2 * v + 1] = setted[v];
            setted[2 * v + 2] = setted[v];
        }
        setted[v] = INF;
    }
    if (added[v] != 0) {
        t[v] += added[v];
        if (tl != tr) {
            added[2 * v + 1] = added[v] + added[2 * v + 1];
            added[2 * v + 2] = added[v] + added[2 * v + 2];
        }
        added[v] = 0;
    }
}
 
void modifyAdd(long long v, long long tl, long long tr, long long l, long long r, long long int val) {
    push(v, tl, tr);
    if (r < tl || tr < l) {
        return;
    }
    if (l <= tl && tr <= r) {
        added[v] = val;
        push(v, tl, tr);
        return;
    }
    long long tm = tl + (tr - tl) / 2;
    modifyAdd(2 * v + 1, tl, tm, l, r, val);
    modifyAdd(2 * v + 2, tm + 1, tr, l, r, val);
    t[v] = min(t[2 * v + 1], t[2 * v + 2]);
}
 
void modifySet(long long v, long long tl, long long tr, long long l, long long r, long long val) {
    push(v, tl, tr);
    if (r < tl || tr < l) {
        return;
    }
    if (l <= tl && tr <= r) {
        setted[v] = val;
        push(v, tl, tr);
        return;
    }
    long long tm = tl + (tr - tl) / 2;
    modifySet(2 * v + 1, tl, tm, l, r, val);
    modifySet(2 * v + 2, tm + 1, tr, l, r, val);
    t[v] = min(t[2 * v + 1], t[2 * v + 2]);
}
 
long long queryMin(long long v, long long tl, long long tr, long long l, long long r) {
    push(v, tl, tr);
    if (r < tl || tr < l) {
        return INF;
    }
    if (l <= tl && tr <= r) {
        return t[v];
    }
    long long tm = tl + (tr - tl) / 2;
    long long ql = queryMin(2 * v + 1, tl, tm, l, r);
    long long qr = queryMin(2 * v + 2, tm + 1, tr, l, r);
    return min(ql, qr);
}
 
int main() {
 
    int n;
    string s;
    long long int x, y, z;
 
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
 
    build(0, 0, n - 1);
 
    while (cin >> s >> x >> y) {
        if (s == "min") {
            cout << queryMin(0, 0, n - 1, x - 1, y - 1) << endl;
        }
        if (s == "set") {
            cin >> z;
            modifySet(0, 0, n - 1, x - 1, y - 1, z);
        }
        if (s == "add") {
            cin >> z;
            modifyAdd(0, 0, n - 1, x - 1, y - 1, z);
        }
    }
}