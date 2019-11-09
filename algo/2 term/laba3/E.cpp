#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
 
vector<int> dp;
vector<int> aut;
vector<int> level;
vector<int> height;
vector<int> parent;
 
vector<bool> visited;
 
vector<vector<int>> graph1;
vector<vector<int>> graph2;
 
// снм с эвристиками
int getParent(int vertex) {
    if (parent[vertex] == vertex) {
        return vertex;
    }
    return parent[vertex] = getParent(parent[vertex]);
 
}
 
void union1(int x, int y) {
    int cur_x = x;
    x = getParent(x);
    y = getParent(y);
    if (x == y) {
        aut[x] = cur_x;
        return;
    }
    if (height[x] == height[y]) {
        height[x] += 1;
    }
    if (height[x] > height[y]) {
        parent[y] = x;
    } else {
        parent[x] = y;
    }
    aut[getParent(x)] = cur_x;
}
 
void dfs(int vertex, int prev) {
    for (int cur_vertex : graph1[vertex]) {
        if (cur_vertex != prev) {
            level[cur_vertex] = level[vertex] + 1;
            dfs(cur_vertex, vertex);
            union1(vertex, cur_vertex);
        }
    }
    visited[vertex] = true;
    for (int cur_vertex : graph2[vertex]) {
        if (visited[cur_vertex]) {
            int aut_t = aut[getParent(cur_vertex)];
            dp[vertex] = max(dp[vertex], level[vertex] - level[aut_t]);
            dp[cur_vertex] = max(dp[cur_vertex], level[cur_vertex] - level[aut_t]);
        }
    }
}
 
int dfsResult(int vertex, int prev) {
    int result = 0;
    for (int cur_vertex : graph1[vertex]) {
        if (cur_vertex != prev) {
            result += dfsResult(cur_vertex, vertex);
            dp[vertex] = max(dp[vertex], dp[cur_vertex] - 1);
        }
    }
    if (dp[vertex] > 0) {
        result += 1;
    }
    return result;
}
 
int main() {
 
    uint32_t a, b;
    uint32_t n, m;
 
    cin >> n;
 
    dp.resize(n);
    aut.resize(n);
    level.resize(n);
    visited.resize(n);
 
    parent.resize(n);
    height.resize(n);
    graph1.resize(n);
    graph2.resize(n);
 
    for (int i = 0; i < n; i++) {
        aut[i] = i;
        parent[i] = i;
    }
 
    vector<uint32_t> cur_heights(n, 0);
    vector<pair<int, int>> cur_requests(n, {0, 0});
 
    for (int i = 0; i < n - 1; i++) {
        cin >> a >> b;
        a -= 1;
        b -= 1;
        cur_heights[a] += 1;
        cur_heights[b] += 1;
        cur_requests[i] = {a, b};
    }
 
    for (int i = 0; i < n; i++) {
        graph1[i].resize(cur_heights[i]);
        cur_heights[i] = 0;
    }
 
    for (int i = 0; i < n - 1; i++) {
        int first = cur_requests[i].first;
        int second = cur_requests[i].second;
        graph1[first][cur_heights[first]] = second;
        cur_heights[first] += 1;
        graph1[second][cur_heights[second]] = first;
        cur_heights[second] += 1;
    }
 
    cin >> m;
 
    cur_heights.clear();
    cur_requests.clear();
 
    cur_heights.resize(n, 0);
    cur_requests.resize(m, {0, 0});
 
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        cur_heights[--a] += 1;
        cur_heights[--b] += 1;
        cur_requests[i] = {a, b};
    }
 
    for (int i = 0; i < n; i++) {
        graph2[i].resize(cur_heights[i]);
        cur_heights[i] = 0;
    }
 
    for (int i = 0; i < m; i++) {
        int first = cur_requests[i].first;
        int second = cur_requests[i].second;
        graph2[first][cur_heights[first]] = second;
        cur_heights[first] += 1;
        graph2[second][cur_heights[second]] = first;
        cur_heights[second] += 1;
    }
 
    dfs(0, -1);
 
    cout << n - dfsResult(0, -1) - 1 << endl;
 
    return 0;
}