#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
 
struct edge {
 
    int32_t from, to;
    int64_t value;
 
    edge(int32_t from, int32_t to, int64_t value) : from(from), to(to), value(value) {}
};
 
vector<bool> used;
vector<bool> used1;
 
vector<edge> edges;
vector<int64_t> dists;
vector<int64_t> lastRelaxation;
 
vector<vector<int32_t>> graph;
 
void dfs(int32_t u) {
    used[u] = true;
    for (int32_t vertex : graph[u]) {
        if (!used[vertex]) {
            dfs(vertex);
        }
    }
}
 
void dfs1(int32_t u) {
    used1[u] = true;
    for (int32_t vertex : graph[u]) {
        if (!used1[vertex]) {
            dfs1(vertex);
        }
    }
}
 
int main() {
 
    int64_t w;
    int32_t u, v;
    int32_t n, m, s;
 
    cin >> n >> m >> s;
 
    s--;
 
    graph.resize(n);
    lastRelaxation.resize(n);
    dists.resize(n, INT64_MAX);
 
    used.resize(n, false);
    used1.resize(n, false);
 
    for (int32_t i = 0; i < m; i++) {
        cin >> u >> v >> w;
        --u;
        --v;
        graph[u].push_back(v);
        edges.emplace_back(u, v, w);
    }
 
    dfs(s);
 
    dists[s] = 0;
    for (int32_t i = 0; i < n; i++) {
        for (auto cur_edge : edges) {
            if (used[cur_edge.to] && dists[cur_edge.from] < INT64_MAX
                && dists[cur_edge.to] > dists[cur_edge.from] + cur_edge.value) {
                dists[cur_edge.to] = dists[cur_edge.from] + cur_edge.value;
            }
        }
    }
 
    copy(dists.begin(), dists.end(), lastRelaxation.begin());
 
    for (auto cur_edge : edges) {
        if (used[cur_edge.to] && lastRelaxation[cur_edge.from] < INT64_MAX
            && lastRelaxation[cur_edge.to] > lastRelaxation[cur_edge.from] + cur_edge.value) {
            lastRelaxation[cur_edge.to] = lastRelaxation[cur_edge.from] + cur_edge.value;
        }
    }
 
    for (int32_t i = 0; i < n; i++) {
        if (used[i] && lastRelaxation[i] != dists[i]) {
            dfs1(i);
        }
    }
 
    for (int32_t i = 0; i < n; i++) {
        if (dists[i] == INT64_MAX) {
            cout << "*" << endl;
        } else if (used1[i]) {
            cout << "-" << endl;
        } else {
            cout << dists[i] << endl;
        }
    }
 
    return 0;
}