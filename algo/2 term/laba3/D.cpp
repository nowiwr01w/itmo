#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
 
const int MAX_L = 19;
const int MAX_N = 2 * 100000 + 1;
 
int cur_count = 1;
 
// is_dead: 1 - dead, 0 - alive
int depth[MAX_N];
int is_dead[MAX_N];
int alive_parents[MAX_N];
int dp[MAX_N + 1][MAX_L + 1];
 
void add(int parent) {
    cur_count += 1;
    dp[cur_count][0] = parent;
    for (int i = 1; i < MAX_L + 1; i++) {
        dp[cur_count][i] = dp[dp[cur_count][i - 1]][i - 1];
    }
    alive_parents[cur_count] = parent;
    depth[cur_count] = depth[parent] + 1;
}
 
int lca(int first, int second) {
    if (depth[second] < depth[first]) {
        swap(second, first);
    }
    for (int i = MAX_L; i >= 0; i--) {
        int cur_pow = 1 << i;
        if (depth[second] >= cur_pow + depth[first]) {
            second = dp[second][i];
        }
    }
    if (first == second) {
        return first;
    }
    for (int i = MAX_L; i >= 0; i--) {
        if (dp[first][i] != dp[second][i]) {
            first = dp[first][i];
            second = dp[second][i];
        }
    }
    return dp[first][0];
}
 
int findAlive(int vertex) {
    if (is_dead[vertex] == 0) {
        return vertex;
    } else {
        alive_parents[vertex] = findAlive(alive_parents[vertex]);
        return alive_parents[vertex];
    }
}
 
int main() {
 
    char sym;
 
    int n = 0;
    int result = 0;
    int first = 0, second = 0;
 
    int root = 1;
 
    cin >> n;
 
    for (int i = 0; i < MAX_L + 1; i++) {
        dp[root][i] = root;
    }
    depth[root] = 1;
    alive_parents[root] = root;
 
    for (int i = 0; i < n; i++) {
        cin >> sym;
        if (sym == '+') {
            cin >> first;
            add(first);
        }
        if (sym == '-') {
            cin >> first;
            is_dead[first] = 1;
        }
        if (sym == '?') {
            cin >> first >> second;
            result = lca(first, second);
            cout << findAlive(result) << endl;
        }
    }
 
    return 0;
}