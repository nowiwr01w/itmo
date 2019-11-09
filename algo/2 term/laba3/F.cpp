#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
 
const int MAX_L = 19;
const int MAX_N = 100010;
 
int root;
int cur_time = 0;
int walk_pos = 0;
 
int depth[MAX_N];
int time_in[MAX_N];
int first_in[MAX_N];
 
vector<vector<int>> tree(MAX_N);
vector<vector<pair<int, int>>> table(MAX_L, vector<pair<int, int>>(2 * MAX_N, {0, 0}));
 
bool comparison(int first, int second) {
    return time_in[first] < time_in[second];
}
 
inline void dfs(int cur_vertex, int cur_depth) {
    time_in[cur_vertex] = cur_time++;
    depth[cur_vertex] = cur_depth;
    first_in[cur_vertex] = walk_pos;
    table[0][walk_pos++] = {cur_depth, cur_vertex};
    for (int next_vertex : tree[cur_vertex]) {
        dfs(next_vertex, cur_depth + 1);
        table[0][walk_pos] = {cur_depth, cur_vertex};
        walk_pos += 1;
    }
}
 
inline int lca(int first, int second) {
    int min_first_in = min(first_in[first], first_in[second]);
    int max_first_in = max(first_in[first], first_in[second]);
    int length = max_first_in - min_first_in + 1;
    int cur_power = (int) log2(length);
    pair<int, int> result = min(table[cur_power][min_first_in], table[cur_power][max_first_in - (1 << cur_power) + 1]);
    return result.second;
}
 
int main() {
 
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
 
    int n;
    int t, k, m;
    int requests[MAX_N];
 
    cin >> n;
 
    for (int i = 0; i < n; i++) {
        cin >> t;
        if (t == -1) {
            root = i;
        } else {
            t -= 1;
            tree[t].push_back(i);
        }
    }
 
    dfs(root, 1);
 
    for (int i = 1; i < MAX_L; i++) {
        int cur_pow = 1 << (i - 1);
        for (int j = 0; j + cur_pow < walk_pos; j++) {
            table[i][j] = min(table[i - 1][j], table[i - 1][j + cur_pow]);
        }
    }
 
    cin >> m;
 
    for (int i = 0; i < m; ++i) {
        cin >> k;
        if (k == 0) {
            cout << 0 << endl;
            continue;
        }
        for (int j = 0; j < k; ++j) {
            cin >> requests[j];
            requests[j] -= 1;
        }
 
        sort(requests, requests + k, &comparison);
 
        int result = depth[requests[0]];
        for (int j = 1; j < k; ++j) {
            result += depth[requests[j]];
            int cur_lca = lca(requests[j - 1], requests[j]);
            result -= depth[cur_lca];
        }
        cout << result << endl;
    }
 
    return 0;
}