#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
 
const int MAX = 100001;
 
enum {
    BLACK, GREY, WHITE
};
 
int color[MAX];
bool used[MAX];
bool hasCycle = false;
 
vector<int> ans;
vector<vector<int>> graph;
 
void dfs(int vertex) {
    used[vertex] = true;
    for (int u : graph[vertex]) {
        if (!used[u]) {
            dfs(u);
        }
    }
    ans.push_back(vertex);
}
 
void dfs2(int vertex) {
    color[vertex] = GREY;
    for (int u : graph[vertex]) {
        if (color[u] == WHITE) {
            dfs2(u);
        } else
        if (color[u] == GREY) {
            hasCycle = true;
        }
    }
    color[vertex] = BLACK;
}
 
void checkCycle(uint32_t size) {
    for (size_t v = 0; v < size; v++) {
        if (!used[v]) {
            dfs2(v);
        }
    }
}
 
void topSort(uint32_t size) {
    for (size_t v = 0; v < size; v++) {
        if (!used[v]) {
            dfs(v);
        }
    }
    reverse(ans.begin(), ans.end());
}
 
int main() {
 
    uint32_t n, m;
    cin >> n >> m;
    graph.resize(n);
 
    for (size_t i = 0; i < n; i++) {
        color[i] = WHITE;
        used[i] = false;
    }
 
    for (size_t i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph[u].push_back(v);
    }
 
    checkCycle(n);
    if (hasCycle) {
        cout << -1;
        return 0;
    }
 
    topSort(n);
    for (int v : ans) {
        cout << v + 1 << " ";
    }
 
    return 0;
}