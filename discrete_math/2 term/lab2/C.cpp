#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define MODULE 1000000007

enum colors {
    white, gray, black
};

vector<int> top_sort;
vector<bool> visited;
vector<colors> color;
vector<vector<int>> first_graph;
vector<vector<int>> second_graph;

bool topSort(int v) {
    color[v] = gray;
    for (int to : first_graph[v]) {
        if (color[to] == white && topSort(to)) {
            return true;
        }
        if (visited[to] && color[to] == gray) {
            return true;
        }
    }
    color[v] = black;
    top_sort.push_back(v);
    return false;
}

void dfs(int v) {
    visited[v] = true;
    for (int cur_vertex : second_graph[v]) {
        if (visited[cur_vertex] == false) {
            dfs(cur_vertex);
        }
    }
}

int main() {
    
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    freopen("problem3.in", "r", stdin);
    freopen("problem3.out", "w", stdout);

    char sym;

    int m, k;
    unsigned int n;

    int a, b, t;
    int result = 0;

    cin >> n >> m >> k;

    vector<int> terminals;
    vector<int> paths(n, 0);

    paths[0] = 1;
    first_graph.resize(n);
    second_graph.resize(n);

    for (int i = 0; i < k; i++) {
        cin >> t;
        terminals.push_back(--t);
    }

    for (int i = 0; i < m; i++) {
        cin >> a >> b >> sym;
        a -= 1;
        b -= 1;
        first_graph[a].push_back(b);
        second_graph[b].push_back(a);
    }

    visited.assign(n, false);
    for (int i = 0; i < k; i++) {
        dfs(terminals[i]);
    }

    color.assign(n, white);

    bool is_cycle = topSort(0);
    if (is_cycle) {
        cout << "-1" << endl;
        return 0;
    }

    reverse(top_sort.begin(), top_sort.end());

    for (int to : top_sort) {
        for (int j = 0; j < second_graph[to].size(); j++) {
            paths[to] += paths[second_graph[to][j]];
        }
    }

    for (int terminal : terminals) {
        result = (result + paths[terminal]) % MODULE;
    }

    cout << result << endl;;

    return 0;
}