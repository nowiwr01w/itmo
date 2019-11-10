#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
 
int n, m;
vector<int> p;
 
struct Node {
    int v, u, weight;
    explicit Node(int v = 0, int u = 0, int weight = 0) : v(v), u(u), weight(weight) {}
};
 
void make_set() {
    for (size_t i = 0; i < n; i++) {
        p[i] = i;
    }
}
 
int64_t get(int x) {
    if (p[x] != x) {
        p[x] = get(p[x]);
    }
    return p[x];
}
 
void unionn(int a, int b) {
    a = get(a);
    b = get(b);
    if (a != b) {
        p[a] = b;
    }
}
 
int main() {
 
    cin >> n >> m;
    vector<Node> graph(m);
 
    for (size_t i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        graph[i] = Node(--a, --b, c);
    }
 
    p.resize(n);
    sort(graph.begin(), graph.end(), [](Node a, Node b) { return a.weight < b.weight; });
 
    make_set();
 
    uint64_t result = 0;
    for (auto edge : graph) {
        if (get(edge.u) != get(edge.v)) {
            unionn(edge.v, edge.u);
            result += edge.weight;
        }
    }
 
    cout << result << endl;
 
    return 0;
}