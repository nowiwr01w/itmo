#include <map>
#include <set>
#include <vector>
#include <iostream>
using namespace std;
 
vector<bool> used;
vector<int32_t> colors;
vector<int32_t> ordered;
vector<vector<int32_t>> graph;
vector<vector<int32_t>> graph_reversed;
set<pair<int32_t, int32_t>> edges;
 
int32_t color = 0;
 
void first_dfs(int32_t vertex) {
    used[vertex] = true;
    for (auto next: graph[vertex]) {
        if (!used[next]) {
            first_dfs(next);
        }
    }
    ordered.push_back(vertex);
}
 
void second_dfs(int32_t vertex, int32_t cur_color) {
    colors[vertex] = cur_color;
    for (auto cur_vertex : graph_reversed[vertex]) {
        if (colors[cur_vertex] == -1) {
            second_dfs(cur_vertex, cur_color);
        }
    }
}
 
int main() {
 
    int32_t n, m;
    cin >> n >> m;
 
    graph.resize(n + 1);
    graph_reversed.resize(n + 1);
 
    used.assign(n + 1, false);
    colors.assign(n + 1, -1);
 
    for (size_t i = 0; i < m; i++) {
        int32_t first, second;
        cin >> first >> second;
        graph[first].push_back(second);
        graph_reversed[second].push_back(first);
    }
 
    for (size_t i = 1; i <= n; i++) {
        if (!used[i]) {
            first_dfs(i);
        }
    }
 
    for (size_t i = 1; i <= n; i++) {
        // В обратном порядке
        int32_t vertex = ordered[n - i];
        if (colors[vertex] == -1) {
            second_dfs(vertex, color++);
        }
    }
 
    for (size_t i = 1; i < graph.size(); i++) {
        for (size_t j = 0; j < graph[i].size(); j++) {
            auto cur = graph[i][j];
            if (colors[i] != colors[cur]) {
                edges.insert({colors[i], colors[cur]});
            }
        }
    }
 
    cout << edges.size() << endl;
 
    return 0;
}