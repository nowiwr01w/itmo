#include <map>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 100001;

vector<bool> term1(MAXN, false);
vector<bool> term2(MAXN, false);
vector<bool> visited1(MAXN, false);
vector<bool> visited2(MAXN, false);
vector<vector<int>> aut1(MAXN, vector<int>(26, 0));
vector<vector<int>> aut2(MAXN, vector<int>(26, 0));

bool bfs(queue<pair<int, int>> current_queue) {
    pair<int, int> temp = make_pair(1, 1);
    current_queue.push(temp);
    while (!current_queue.empty()) {
        pair<int, int> new_cur = current_queue.front();
        current_queue.pop();
        if (term1[new_cur.first] != term2[new_cur.second]) {
            return false;
        }
        for (int i = 0; i < 26; i++) {
            int u = aut1[new_cur.first][i];
            int v = aut2[new_cur.second][i];
            if (!visited1[u] || !visited2[v]) {
                visited1[u] = visited2[v] = true;
                current_queue.push(make_pair(u, v));
            }
        }
    }
    return true;
}

int main() {

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    freopen("isomorphism.in", "r", stdin);
    freopen("isomorphism.out", "w", stdout);

    char symbol;
    int a, b, t;
    int n, m, k;
    int n1, m1, k1;
    queue<pair<int, int>> current_queue;

    cin >> n >> m >> k;

    for (int i = 0; i < k; i++) {
        cin >> t;
        term1[t] = true;
    }

    for (int i = 0; i < m; i++) {
        cin >> a >> b >> symbol;
        aut1[a][symbol - 'a'] = b;
    }

    cin >> n1 >> m1 >> k1;

    for (int i = 0; i < k1; i++) {
        cin >> t;
        term2[t] = true;
    }

    for (int i = 0; i < m1; i++) {
        cin >> a >> b >> symbol;
        aut2[a][symbol - 'a'] = b;
    }

    if (bfs(current_queue)) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }

    return 0;
}