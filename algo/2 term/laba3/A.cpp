#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
 
vector<bool> visited;
vector<uint32_t> depth;
vector<uint32_t> parents;
 
void dfs(int vertex) {
    visited[vertex] = true;
    if (!visited[parents[vertex]]) {
        dfs(parents[vertex]);
    }
    depth[vertex] = depth[parents[vertex]] + 1;
}
 
int main() {
 
    uint32_t a, n;
    uint32_t root;
 
    cin >> n;
 
    uint32_t cur_log = (uint32_t) log2(n);
 
    depth.resize(n + 1);
    parents.resize(n + 1);
    visited.resize(n + 1);
    vector<vector<uint32_t>> dp(n + 1, vector<uint32_t>(cur_log + 1, 0));
 
    for (uint32_t i = 1; i < n + 1; i++) {
        cin >> a;
        if (a == 0) {
            root = i;
            parents[i] = i;
            continue;
        }
        parents[i] = a;
    }
 
    for (int i = 1; i < n + 1; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }
 
    for (int i = 1; i < n + 1; i++) {
        dp[i][0] = parents[i];
    }

    for (int j = 1; j < cur_log + 1; j++) {
        for (int i = 1; i < n + 1; i++) {
            if (pow(2, j) < depth[i]) {
                dp[i][j] = dp[dp[i][j - 1]][j - 1];
            }
        }
    }
 
 
    for (int i = 1; i < n + 1; i++) {
        cout << i << ": ";
        for (int j = 0; j < cur_log + 1; j++) {
            if (i == root) {
                continue;
            }
            if (dp[i][j] > 0) {
                cout << dp[i][j] << " ";
            }
        }
        cout << endl;
    }
 
    return 0;
}