#include <set>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define MODULE 1000000007

int main() {

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    freopen("problem4.in", "r", stdin);
    freopen("problem4.out", "w", stdout);

    char sym;

    int m, k, l;
    int a, b, t;

    unsigned int n;
    unsigned long long answer = 0;

    set<int> states;
    vector<int> terminals;

    states.emplace(0);

    cin >> n >> m >> k >> l;

    vector<int> result(n, 0);
    vector<bool> flags(n, false);

    vector<vector<int>> graph;

    result[0] = 1;
    graph.resize(n);

    for (int i = 0; i < k; i++) {
        cin >> t;
        t -= 1;
        flags[t] = true;
        terminals.push_back(t);
    }

    for (int i = 0; i < m; i++) {
        cin >> a >> b >> sym;
        a -= 1;
        b -= 1;
        graph[a].push_back(b);
    }

    for (int i = 0; i < l; i++) {
        set<int> temp_states;
        vector<int> temp_result(n, 0);
        for (int state : states) {
            for (unsigned j = 0; j < graph[state].size(); j++) {
                long long to = graph[state][j];
                temp_result[to] = (temp_result[to] + result[state]) % MODULE;
                temp_states.emplace(to);
            }
        }
        states = temp_states;
        result = temp_result;
    }

    for (unsigned i = 0; i < result.size(); i++) {
        if (flags[i]) {
            answer = (answer + result[i]) % MODULE;
        }
    }

    cout << answer << endl;

    return 0;
}