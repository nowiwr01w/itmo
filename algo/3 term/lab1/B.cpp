#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
 
vector<bool> used;
set<uint64_t> brides;
vector<uint64_t> ret;
vector<uint64_t> time_in;
vector<set<int64_t>> graph;
map<pair<uint64_t, uint64_t>, uint64_t> number_of_edge;
 
uint64_t timer = 0;
 
void dfs(uint64_t vertex, uint64_t parent) {
    used[vertex] = true;
    time_in[vertex] = ++timer;
    ret[vertex] = timer;
    for (auto cur_vertex : graph[vertex]) {
        if (cur_vertex == parent) {
            continue;
        }
        if (used[cur_vertex]) {
            ret[vertex] = min(ret[vertex], time_in[cur_vertex]);
        }
        else {
            dfs(cur_vertex, vertex);
            ret[vertex] = min(ret[vertex], ret[cur_vertex]);
        }
        if (ret[cur_vertex] > time_in[vertex]) {
            brides.insert(number_of_edge[{vertex, cur_vertex}]);
        }
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
 
    cout << brides.size() << endl;
    for (uint64_t v : brides) {
        cout << v << ' ';
    }
 
    return 0;
}