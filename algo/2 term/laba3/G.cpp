#include <vector>
#include <iostream>
using namespace std;
 
const uint32_t MAX_LOG = 19;
const uint32_t MAX_N = 3 * 100000;
 
int cur_time = 0;
 
int time_in[MAX_N];
int time_out[MAX_N];
 
int parents[MAX_N];
int dp[MAX_N][MAX_LOG];
 
uint64_t t[4 * MAX_N];
 
vector<vector<uint32_t>> ways;
 
void dfs(int cur, int prev) {
    time_in[cur] = cur_time++;
    if (prev == -1) {
        parents[cur] = 0;
    } else {
        parents[cur] = prev;
    }
    for (auto tr : ways[cur]) {
        if (tr != prev) {
            dfs(tr, cur);
        }
    }
    time_out[cur] = cur_time - 1;
}
 
bool parent(int u, int v) {
    return (time_in[u] <= time_in[v] && time_out[v] <= time_out[u]);
}
 
int lca(int x, int y) {
    if (parent(x, y)) {
        return x;
    }
    for (int i = MAX_LOG - 1; i >= 0; i--) {
        if (!parent(dp[x][i], y)) {
            x = dp[x][i];
        }
    }
    return parents[x];
}
 
void update(int v, int vl, int vr, int pos, long long val) {
    if (vl == vr) {
        t[v] += val;
        return;
    }
    if (vl > vr) {
        return;
    }
    int vm = vl + (vr - vl) / 2;
    if (pos <= vm) {
        update(2 * v + 1, vl, vm, pos, val);
    } else {
        update(2 * v + 2, vm + 1, vr, pos, val);
    }
    t[v] = t[2 * v + 1] + t[2 * v + 2];
}
 
uint64_t sum(int v, int vl, int vr, int l, int r) {
    if (l > vr || r < vl) {
        return 0;
    }
    if (vl == l && vr == r) {
        return t[v];
    }
    int vm = vl + (vr - vl) / 2;
    uint64_t ql = sum(2 * v + 1, vl, vm, l, min(vm, r));
    uint64_t qr = sum(2 * v + 2, vm + 1, vr, max(vm + 1, l), r);
    return ql + qr;
}
 
int main() {
    
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
 
    char sym;
 
    uint32_t n, m;
    uint32_t u, v;
 
    uint64_t d;
    uint64_t result;
 
    cin >> n;
 
    ways.resize(n + 1);
    ways[0].push_back(1);
    ways[1].push_back(0);
 
    for (int i = 0; i < n - 1; i++) {
        cin >> v >> u;
        ways[v].push_back(u);
        ways[u].push_back(v);
    }
 
    dfs(0, -1);
 
    for (int i = 0; i < n + 1; i++) {
        dp[i][0] = parents[i];
    }
    for (int j = 1; j < MAX_LOG; j++) {
        for (int i = 0; i < n + 1; i++) {
            dp[i][j] = dp[dp[i][j - 1]][j - 1];
        }
    }
 
    cin >> m;
 
    for (int i = 0; i < m; i++) {
        cin >> sym;
        if (sym == '+') {
            cin >> v >> u >> d;
            update(0, 0, n + 1, time_in[v], d);
            update(0, 0, n + 1, time_in[u], d);
            update(0, 0, n + 1, time_in[lca(v, u)], -d);
            update(0, 0, n + 1, time_in[parents[lca(v, u)]], -d);
        }
        if (sym == '?') {
            cin >> v;
            result =  sum(0, 0, n + 1, time_in[v], time_out[v]);
            cout << result << '\n';
        }
    }
 
    return 0;
}