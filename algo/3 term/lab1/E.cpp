#include <map>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
 
uint64_t n, m;
uint64_t timer = 0;
uint64_t componentCount = 0;
 
vector<bool> used;
vector<uint64_t> up;
vector<uint64_t> tin;
vector<uint64_t> component;
vector<vector<uint64_t>> graph;
map<uint64_t, pair<uint64_t, uint64_t>> edges;
 
void read_undirected_graph() {
 
    cin >> n >> m;
 
    up.resize(n + 1);
    tin.resize(n + 1);
    graph.resize(n + 1);
    component.assign(m + 1, 0);
    used.assign(n + 1, false);
 
    for (uint64_t i = 1; i <= m; ++i) {
        uint64_t vertex_1, vertex_2;
        cin >> vertex_1 >> vertex_2;
        graph[vertex_1].push_back(i);
        graph[vertex_2].push_back(i);
        edges[i] = {vertex_1, vertex_2};
    }
}
 
 
void setComponentColor(uint64_t vertex, uint64_t from_vertex, uint64_t color) {
    used[vertex] = true;
    for (uint64_t cur_vertex: graph[vertex]) {
        if (cur_vertex == from_vertex) {
            continue;
        }
        auto edge = edges[cur_vertex];
        auto u = edge.first;
        if (u == vertex) {
            u = edge.second;
        }
        if (!used[u]) {
            if (tin[vertex] <= up[u]) {
                component[cur_vertex] = ++componentCount;
                setComponentColor(u, cur_vertex, componentCount);
            } else {
                component[cur_vertex] = color;
                setComponentColor(u, cur_vertex, color);
            }
        } else if (tin[vertex] > tin[u]) {
            component[cur_vertex] = color;
        }
    }
}
 
 
void dfs(uint64_t vertex, uint64_t from_vertex) {
    ++timer;
    used[vertex] = true;
    tin[vertex] = up[vertex] = timer;
    for (uint64_t cur_vertex: graph[vertex]) {
        if (cur_vertex == from_vertex) {
            continue;
        }
        auto edge = edges[cur_vertex];
        auto u = edge.first;
        if (u == vertex) {
            u = edge.second;
        }
        if (used[u]) {
            up[vertex] = min(up[vertex], tin[u]);
        }
        else {
            dfs(u, cur_vertex);
            up[vertex] = min(up[vertex], up[u]);
        }
    }
}
 
 
int main() {
 
    read_undirected_graph();
 
    for (uint64_t i = 1; i <= n; i++) {
        if (used[i] == 0) {
            dfs(i, 0);
        }
    }
 
    used.assign(n + 1, false);
 
    for (uint64_t i = 1; i <= n; i++) {
        if (!used[i]) {
            setComponentColor(i, 0, componentCount);
        }
    }
 
    cout << componentCount << endl;
    for (uint64_t i = 1; i <= m; i++) {
        cout << component[i] << ' ';
    }
 
    return 0;
}