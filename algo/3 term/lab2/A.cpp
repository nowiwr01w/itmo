#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
 
int main() {
 
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
 
    int n;
    vector<vector<int>> graph;
 
    cin >> n;
 
    graph.assign(n + 1, vector<int>(n + 1));
 
    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            cin >> graph[i][j];
        }
    }
 
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
            }
        }
    }
 
    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            cout << graph[i][j] << ' ';
        }
        cout << endl;
    }
 
    return 0;
}