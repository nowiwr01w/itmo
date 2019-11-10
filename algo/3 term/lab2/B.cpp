#include <set>
#include <vector>
#include <iostream>
using namespace std;
 
uint64_t n = 0, m = 0;
 
vector<int64_t> result;
vector<set<pair<int64_t, int64_t>>> graph;
 
void dijkstra() {
 
    set<pair<int64_t, int64_t>> container;
    container.insert({0, 1});
 
    while (!container.empty()) {
        auto temp = *container.begin();
        container.erase(container.begin());
        for (auto cur_edge : graph[temp.second]) {
            if (result[cur_edge.second] > result[temp.second] + cur_edge.first) {
                result[cur_edge.second] = result[temp.second] + cur_edge.first;
                container.erase(cur_edge);
                container.insert(cur_edge);
            }
        }
    }
}
 
 
int main() {
 
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
 
    cin >> n >> m;
 
    result.assign(n + 1, INT64_MAX);
 
    // weight to number
    graph.assign(n + 1, set<pair<int64_t, int64_t>>());
 
    result[0] = result[1] = 0;
 
    for (uint64_t i = 0; i < m; i++) {
        int64_t from, to, weight;
        cin >> from >> to >> weight;
        graph[from].insert({weight, to});
        graph[to].insert({weight, from});
    }
 
    dijkstra();
 
    for (uint64_t i = 1; i < result.size(); i++) {
        cout << result[i] << ' ';
    }
 
    return 0;
}