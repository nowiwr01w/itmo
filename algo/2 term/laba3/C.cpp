#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
 
int64_t cur_min;
vector<int64_t> depth;
vector<vector<pair<int64_t, int64_t>>> dp;
 
void lca(int64_t v, int64_t u, int64_t length) {
    cur_min = INT64_MAX;
    if (depth[v] > depth[u]) {
        swap(u, v);
    }
    for (int64_t i = length - 1; i >= 0; --i) {
        if (pow(2, i) <= (depth[u] - depth[v])) {
            cur_min = min(cur_min, dp[u][i].second);
            u = dp[u][i].first;
        }
    }
    if (v == u) {
        return;
    }
    for (int64_t i = length - 1; i >= 0; i--) {
        if (dp[v][i] != dp[u][i]) {
            cur_min = min(min(cur_min, dp[v][i].second), dp[u][i].second);
            v = dp[v][i].first;
            u = dp[u][i].first;
        }
    }
}
 
int main() {
 
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    freopen("minonpath.in", "r", stdin);
    freopen("minonpath.out", "w", stdout);
 
    uint32_t n = 0, m = 0;
 
    int64_t from = 0, cost = 0;
    int64_t first = 0, second = 0;
 
    pair<int64_t, int64_t> to;
    pair<int64_t, int64_t> cur;
 
    cin >> n;
 
    uint32_t cur_log = (uint32_t) log2(n) + 1;
 
    depth.resize(n, 0);
    dp.resize(n, vector<pair<int64_t, int64_t>>(cur_log));
 
    for (int64_t i = 0; i < cur_log; i++) {
        dp[0][i] = make_pair(0, INT64_MAX);
    }
 
    for (int64_t i = 1; i < n; i++) {
        cin >> from >> cost;
        from -= 1;
        dp[i][0] = make_pair(from, cost);
        depth[i] = depth[from] + 1;
    }
 
    for (int64_t j = 1; j < cur_log; j++) {
        for (int64_t i = 1; i < n; i++) {
            cur = dp[i][j - 1];
            to = dp[cur.first][j - 1];
            dp[i][j] = make_pair(to.first, min(cur.second, to.second));
        }
    }
 
    cin >> m;
 
    for (int64_t i = 0; i < m; i++) {
        cin >> first >> second;
        lca(first - 1, second - 1, cur_log);
        cout << cur_min << endl;
    }
 
    return 0;
}