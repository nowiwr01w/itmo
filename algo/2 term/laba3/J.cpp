#include <vector>
#include <iostream>
using namespace std;
 
const int MAX_N = 100000;
 
vector<int> level(2 * MAX_N, -1);
vector<int> decomposition(2 * MAX_N);
 
vector<vector<int>> edges(2 * MAX_N);
 
int dfs_counting(int vertex, int size, int &centroid, int prev = -1) {
    int s = 1;
    for (auto to: edges[vertex]) {
        if (level[to] == -1 && to != prev) {
            s += dfs_counting(to, size, centroid, vertex);
        }
    }
    if (size <= 2 * s || prev == -1) {
        if (centroid == -1) {
            centroid = vertex;
        }
    }
    return s;
}
 
void dfs(int vertex, int size, int depth, int last) {
    int centroid = -1;
    dfs_counting(vertex, size, centroid);
    level[centroid] = depth;
    decomposition[centroid] = last;
    for (auto to: edges[centroid]) {
        if (level[to] == -1) {
            dfs(to, size / 2, depth + 1, centroid);
        }
    }
}
 
int main() {
 
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
 
    int n;
    int u, v;
 
    cin >> n;
 
    for (int i = 0; i < n - 1; i++) {
        cin >> u >> v;
	u -= 1;
	v -= 1;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
 
    dfs(0, n, 0, -1);
 
    for (int i = 0; i < n; i++) {
        cout << decomposition[i] + 1 << ' ';
    }
 
    return 0;
}