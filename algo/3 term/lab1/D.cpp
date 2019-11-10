#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
 
const int MAX_N = 20001;
 
vector<int> tin;
vector<int> used;
vector<int> component;
vector<bool> result;
vector<vector<pair<int, int>>> graph;
 
int componentCount = 0;
 
int dfs(int vertex, int parent, int depth) {
    int minimum = depth;
    used[vertex] = true;
    tin[vertex] = depth;
    for (auto &cur_edge : graph[vertex]) {
        if (!used[cur_edge.first]) {
            minimum = min(minimum, dfs(cur_edge.first, cur_edge.second, depth + 1));
        } else if (parent != cur_edge.second) {
            minimum = min(minimum, tin[cur_edge.first]);
        }
    }
    if (minimum == depth && parent != -1) {
        result[parent - 1] = true;
    }
    return minimum;
}
 
void setComponentColor(int vertex, int color) {
    component[vertex] = color;
    for (auto &cur_edge : graph[vertex]) {
        if (component[cur_edge.first] == 0) {
            if (result[cur_edge.second - 1]) {
                setComponentColor(cur_edge.first, ++componentCount);
            } else {
                setComponentColor(cur_edge.first, color);
            }
        }
    }
}
 
int main() {
 
    int n, m;
    cin >> n >> m;
 
    graph.resize(n);
    result.resize(m);
 
    tin.resize(MAX_N, 0);
    used.resize(MAX_N, false);
    component.resize(MAX_N, 0);
 
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        graph[u].emplace_back(v, i);
        graph[v].emplace_back(u, i);
    }
 
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs(i, -1, 0);
        }
    }
 
    for (int i = 0; i < n; i++) {
        if (component[i] == 0) {
            setComponentColor(i, ++componentCount);
        }
    }
 
    cout << componentCount << endl;
    for (int i = 0; i < n; i++) {
        cout << component[i] << " ";
    }
 
    return 0;
}