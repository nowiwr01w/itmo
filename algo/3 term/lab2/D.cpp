#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
 
struct edge {
 
    int64_t value;
    uint64_t from, to;
 
    edge(uint64_t from, uint64_t to, int64_t value) : from(from), to(to), value(value) {}
 
};
 
int64_t start;
int64_t n, m, k;
 
vector<edge> edges;
vector<vector<int64_t>> result;
 
void read_graph() {
 
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
 
    int64_t from, to, weight;
    cin >> n >> m >> k >> start;
 
    result.assign(k + 1, vector<int64_t>(n + 1, INT64_MAX));
 
    for (uint64_t i = 1; i <= m; ++i) {
        cin >> from >> to >> weight;
        edges.emplace_back(from, to, weight);
    }
 
}
 
void shortest_k_path() {
 
    result[0][start] = 0;
 
    for (uint64_t i = 1; i <= k; ++i) {
        for (auto &edge : edges) {
            if (result[i - 1][edge.from] < INT64_MAX) {
                result[i][edge.to] = min(result[i][edge.to], result[i - 1][edge.from] + edge.value);
            }
        }
    }
 
}
 
 
int main() {
 
    read_graph();
    shortest_k_path();
 
    for (uint64_t i = 1; i <= n; ++i) {
        if (result[k][i] == INT64_MAX) {
            cout << -1 << endl;
        } else {
            cout << result[k][i] << endl;
        }
    }
 
    return 0;
}