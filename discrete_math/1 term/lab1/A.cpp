#include <vector> 
#include <iostream>
using namespace std;
 
vector<vector<int>> graph, graph_impl;
 
int getVertex(int vertex) {
    if (vertex >= 0) {
        return 2 * vertex - 2;
    }
    return 2 * (-vertex) - 1;
}
 
void dfs(vector<int> &used, vector<int> &checked, int vertex) {
    used[vertex] = 1;
    for (int i = 0; i < graph[vertex].size(); i++) {
        int to = graph[vertex][i];
        if (used[to] == false) {
            dfs(used, checked, to);
        }
    }
    checked.push_back(vertex);
}
 
void dfsComp(vector<int> &check_comp, int vertex, int comp) {
    check_comp[vertex] = comp;
    for (int i = 0; i < graph_impl[vertex].size(); i++) {
        int to = graph_impl[vertex][i];
        if (check_comp[to] == -1) {
            dfsComp(check_comp, to, comp);
        }
    }
}
 
int main() {
 
    int n, m;
    int a, b;
    cin >> n >> m;
 
    vector<int> checked;
    vector<int> used(2 * n, 0);
    vector<int> check_comp(2 * n, -1);
 
    graph.resize(2 * n);
    graph_impl.resize(2 * n);
 
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        a = getVertex(a); 
        b = getVertex(b);
        graph[a ^ 1].push_back(b);   
        graph[b ^ 1].push_back(a);
        graph_impl[a].push_back(b ^ 1);
        graph_impl[b].push_back(a ^ 1);  
    }
 
    for (int i = 0; i < 2 * n; i++) {
        if (used[i] == false) {
            dfs(used, checked, i);
        }
    }
 
    int comp = 0;
    for (int i = 0; i < 2 * n; i++) {
        int vertex = checked[2 * n - i - 1];
        if (check_comp[vertex] == -1) {
            dfsComp(check_comp, vertex, comp);
            comp += 1;
        }
    }
 
    for (int i = 0; i < 2 * n; i += 2) {
        if (check_comp[i] == check_comp[i ^ 1]) {
            cout << "YES" << endl;
            //system("pause");
            return 0;
        }
    }
 
    cout << "NO" << endl;
 
    //system("pause");
    return 0;
}