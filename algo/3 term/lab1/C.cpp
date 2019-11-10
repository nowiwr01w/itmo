#include <set>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
 
vector<bool> used;
set<uint64_t> points;
vector<uint64_t> ret;
vector<uint64_t> time_in;
vector<set<int64_t>> graph;
map<pair<uint64_t, uint64_t>, uint64_t> number_of_edge;
 
uint64_t timer = 0;
 
void dfs(uint64_t vertex, uint64_t parent) {
    used[vertex] = true;
    time_in[vertex] = ++timer;
    ret[vertex] = timer;
    int64_t amount_children = 0;
    for (auto cur_vertex : graph[vertex]) {
        if (cur_vertex == parent) {
            continue;
        }
        if (used[cur_vertex] == 1) {
            ret[vertex] = min(ret[vertex], time_in[cur_vertex]);
        }
        else {
            dfs(cur_vertex, vertex);
            ret[vertex] = min(ret[vertex], ret[cur_vertex]);
            if (time_in[vertex] <= ret[cur_vertex] && parent != 0) {
                points.insert(vertex);
            }
            amount_children++;
        }
 
    }
    if (parent == 0 && amount_children > 1) {
        points.insert(vertex);
    }
 
}
 
int main() {
 
    uint64_t n, m;
    cin >> n >> m;
 
    ret.resize(n + 1);
    graph.resize(n + 1);
    time_in.resize(n + 1);
    used.assign(n + 1, false);
 
    time_in[0] = INT64_MAX;
 
    for (uint64_t i = 1; i <= m; i++) {
        uint64_t vertex_1, vertex_2;
        cin >> vertex_1 >> vertex_2;
        number_of_edge[{vertex_1, vertex_2}] = i;
        number_of_edge[{vertex_2, vertex_1}] = i;
        graph[vertex_1].insert(vertex_2);
        graph[vertex_2].insert(vertex_1);
    }
 
    for (uint64_t i = 1; i <= n; i++) {
        if (!used[i]) {
            dfs(i, 0);
        }
    }
 
    cout << points.size() << endl;
    for (uint64_t v : points) {
        cout << v << ' ';
    }
 
    return 0;
}