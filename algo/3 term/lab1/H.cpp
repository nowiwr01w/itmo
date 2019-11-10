#include <vector>
#include <iostream>
using namespace std;
 
const int MAX_N = 1001;
 
int n;
int ans, reversed_ans;
 
vector<bool> used;
vector<bool> reversed_used;
 
vector<vector<uint32_t>> graph;
vector<vector<uint32_t>> reversed_graph;
 
void dfs1(int vertex, int cur_min) {
    used[vertex] = true;
    ans++;
    for (int cur_vertex = 0; cur_vertex < n; cur_vertex++)
        if (!used[cur_vertex] && graph[vertex][cur_vertex] <= cur_min)
            dfs1(cur_vertex, cur_min);
}
 
void dfs2(int vertex, int cur_min) {
    reversed_used[vertex] = true;
    reversed_ans++;
    for (int cur_vertex = 0; cur_vertex < n; cur_vertex++) {
        if (!reversed_used[cur_vertex] && reversed_graph[vertex][cur_vertex] <= cur_min) {
            dfs2(cur_vertex, cur_min);
        }
    }
}
 
int main() {
 
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    freopen("avia.in", "r", stdin);
    freopen("avia.out", "w", stdout);
 
    cin >> n;
 
    used.resize(MAX_N);
    reversed_used.resize(MAX_N);
 
    graph.resize(MAX_N);
    reversed_graph.resize(MAX_N);
 
    for (int i = 0; i < MAX_N; i++) {
        graph[i].resize(MAX_N);
        reversed_graph[i].resize(MAX_N);
    }
 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
            reversed_graph[j][i] = graph[i][j];
        }
    }
 
    int64_t left = -1;
    int64_t right = MAX_N * MAX_N * MAX_N;
 
    while (right - left > 1) {
        int64_t middle = left - (left - right) / 2;
        for (int i = 0; i < n; i++) {
            used[i] = reversed_used[i] = false;
        }
        ans = reversed_ans = 0;
        dfs1(0, middle);
        dfs2(0, middle);
        if (ans < n || reversed_ans < n) {
            left = middle;
        } else {
            right = middle;
        }
    }
 
    cout << right << endl;
 
    return 0;
}