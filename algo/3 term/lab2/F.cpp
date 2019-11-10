#include <set>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
 
vector<bool> used;
vector<vector<pair<uint64_t, uint64_t>>> graph;
 
void dfs(uint64_t vertex) {
    used[vertex] = true;
    for (auto cur_vertex : graph[vertex]) {
        if (!used[cur_vertex.first]) {
            dfs(cur_vertex.first);
        }
    }
}
 
 
void dijkstra(uint64_t start, uint64_t n, vector<uint64_t> &result) {
 
    result.assign(n, INT64_MAX);
    result[start] = 0;
 
    set<pair<uint64_t, uint32_t>> container;
    container.insert({0, start});
 
    while (!container.empty()) {
        auto temp = *container.begin();
        container.erase(container.begin());
        for (auto cur_edge : graph[temp.second]) {
            if (result[cur_edge.first] > result[temp.second] + cur_edge.second) {
                container.erase({result[cur_edge.first], cur_edge.first});
                result[cur_edge.first] = result[temp.second] + cur_edge.second;
                container.insert({result[cur_edge.first], cur_edge.first});
            }
        }
    }
 
}
 
int main() {
 
    uint64_t n, m;
    uint64_t a, b, c;
    uint64_t u, v, w;
 
    cin >> n >> m;
 
    vector<uint64_t> resultA(n);
    vector<uint64_t> resultB(n);
    vector<uint64_t> resultC(n);
 
    used.resize(n);
    graph.resize(n);
 
    for (uint64_t i = 0; i < m; i++) {
        cin >> u >> v >> w;
        u -= 1;
        v -= 1;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }
 
    cin >> a >> b >> c;
 
    a -= 1;
    b -= 1;
    c -= 1;
 
    dfs(a);
    if (!used[b] || !used[c]) {
        cout << -1 << endl;
        return 0;
    }
 
    used.assign(n, false);
 
    dfs(b);
    if (!used[a] || !used[c]) {
        cout << -1 << endl;
        return 0;
    }
 
    used.assign(n, false);
 
    dfs(c);
    if (!used[a] || !used[b]) {
        cout << -1 << endl;
        return 0;
    }
 
    dijkstra(a, n, resultA);
    dijkstra(b, n, resultB);
    dijkstra(c, n, resultC);
 
    uint64_t a_b = resultA[b];
    uint64_t a_c = resultA[c];
    uint64_t b_c = resultB[c];
    uint64_t b_a = resultB[a];
    uint64_t c_a = resultC[a];
    uint64_t c_b = resultC[b];
 
    vector<uint64_t> paths = {a_b + b_c, a_c + c_b, b_a + a_c, b_c + c_a, c_a + a_b, c_b + b_a};
    sort(paths.begin(), paths.end());
 
    cout << paths[0] << endl;
 
    return 0;
}