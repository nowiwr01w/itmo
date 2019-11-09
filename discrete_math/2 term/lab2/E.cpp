#include <map>
#include <set>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 100;
const long long MOD = 1000000007;

struct edge {
    int to;
    char symbol;
};

bool terminals[MAXN * MAXN];
vector<edge> dka[MAXN * MAXN];
long long res[MAXN * MAXN][MAXN * MAXN];

long long getAnswer(int vertex, int length) {
    if (res[vertex][length] != -1) {
        return res[vertex][length];
    }

    if (length == 0) {
        if (terminals[vertex]) {
            res[vertex][length] = 1;
        }
        else {
            res[vertex][length] = 0;
        }
        return res[vertex][length];
    }

    res[vertex][length] = 0;
    for (unsigned int i = 0; i < dka[vertex].size(); i++) {
        int to = dka[vertex][i].to;
        res[vertex][length] = (res[vertex][length] + getAnswer(to, length - 1)) % MOD;
    }

    return res[vertex][length];
}

int main() {

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    freopen("problem5.in", "r", stdin);
    freopen("problem5.out", "w", stdout);

    char symbol;
    int cnt = 0;
    int a, b, t;
    int n, m, k, l;
    cin >> n >> m >> k >> l;

    bool n_term[MAXN];
    set<int> current_set;
    vector<edge> nka[MAXN];
    map<set<int>, int> number;
    set<set<int>> current_set1;
    queue<set<int>> current_queue;

    // Inicialization
    for (unsigned int i = 0; i < MAXN; i++) {
        n_term[i] = false;
    }

    for (unsigned int i = 0; i < MAXN * MAXN; i++) {
        terminals[i] = false;
        for (int j = 0; j <= l; j++) {
            res[i][j] = -1;
        }
    }

    for (unsigned int i = 0; i < k; i++) {
        cin >> t;
        n_term[t - 1] = true;
    }

    for (unsigned int i = 0; i < m; i++) {
        cin >> a >> b >> symbol;
        a -= 1;
        b -= 1;
        nka[a].push_back({ b, symbol });
    }

    // Tompson alg
    current_set.insert(0);
    current_queue.push(current_set);
    current_set1.insert(current_set);
    number[current_set] = cnt;
    cnt += 1;
    if (n_term[0]) {
        terminals[0] = true;
    }
    while (!current_queue.empty()) {
        set<int> current_vec = current_queue.front();
        current_queue.pop();
        for (char symbol = 'a'; symbol <= 'z'; ++symbol) {
            set<int> to;
            for (auto vertex : current_vec) {
                for (unsigned int j = 0; j < (int)nka[vertex].size(); ++j) {
                    if (nka[vertex][j].symbol == symbol) {
                        to.insert(nka[vertex][j].to);
                    }
                }
            }
            if (to.empty()) {
                continue;
            }
            if (current_set1.count(to) == 0) {
                current_queue.push(to);
                current_set1.insert(to);
                number[to] = cnt;
                for (auto vertex : to) {
                    if (n_term[vertex]) {
                        terminals[cnt] = true;
                        break;
                    }
                }
                cnt += 1;
            }
            int n_to = number[to];
            int n_from = number[current_vec];
            dka[n_from].push_back({ n_to, symbol });
        }
    }

    cout << getAnswer(0, l) << endl;

    return 0;
}