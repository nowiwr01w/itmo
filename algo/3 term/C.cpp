#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
 
struct edge {
 
    int64_t value;
    uint64_t to, from;
 
    edge(uint64_t from, uint64_t to, int64_t value) : from(from), to(to), value(value) {}
};
 
uint64_t n;
vector<edge> edges;
 
vector<int64_t> path;
vector<int64_t> cycle;
vector<int64_t> result;
 
void read_graph() {
 
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
 
    cin >> n;
 
    path.assign(n + 1, -1);
    result.assign(n + 1, 0);
 
    int64_t temp;
    result[0] = result[1] = 0;
 
    for (uint64_t i = 1; i <= n; i++) {
        for (uint64_t j = 1; j <= n; j++) {
            cin >> temp;
            if (temp != 100000) {
                edges.emplace_back(i, j, temp);
            }
        }
    }
 
}
 
void ford_bellman() {
 
    int64_t was_changed = -1;
    for (uint64_t i = 0; i < n; i++) {
        was_changed = -1;
        for (auto &edge : edges) {
            if (result[edge.from] < INT64_MAX) {
                if (result[edge.to] > result[edge.from] + edge.value) {
                    result[edge.to] = max(INT64_MIN, result[edge.from] + edge.value);
                    path[edge.to] = edge.from;
                    was_changed = edge.to;
                }
            }
        }
    }
 
    if (was_changed == -1) {
        cout << "NO";
        return;
    }
 
    for (uint64_t i = 0; i < n; i++) {
        was_changed = path[was_changed];
    }
 
    int64_t path_end = was_changed;
    cycle.push_back(was_changed);
 
    while (path_end != path[was_changed]) {
        was_changed = path[was_changed];
        cycle.push_back(was_changed);
    }
 
    cout << "YES" << endl;
    cout << cycle.size() << endl;
 
    reverse(cycle.begin(), cycle.end());
 
    for (int64_t &i : cycle) {
        cout << i << ' ';
    }
 
}
 
int main() {
 
    read_graph();
    ford_bellman();
 
    return 0;
}