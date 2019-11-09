#include <set>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

int main() {

    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    freopen("problem2.in", "r", stdin);
    freopen("problem2.out", "w", stdout);

    char sym;
    bool flag = false;

    int m, k;
    int a, b, t;

    unsigned int n;
    string cur_string;

    set<int> states;

    states.emplace(0);
    
    cin >> cur_string;
    cin >> n >> m >> k;

    vector<bool> terminal_states(n, false);
    for (int i = 0; i < k; i++) {
        cin >> t;
        terminal_states[--t] = true;
    }

    vector<vector<vector<int>>> transitions(n);
    for (int i = 0; i < n; i++) {
        transitions[i].resize('z' - 'a' + 1);
    }

    for (int i = 0; i < m; i++) {
        cin >> a >> b >> sym;
        a -= 1;
        b -= 1;
        transitions[a][sym - 'a'].push_back(b);
    }

    for (char cur_symbol : cur_string) {
        set<int> temp_states;
        for (int state : states) {
            for (int &cur_condition : transitions[state][cur_symbol - 'a']) {
                temp_states.emplace(cur_condition);
            }
        }
        states = temp_states;
    }

    for (int state : states) {
        if (terminal_states[state]) {
            flag = true;
            break;
        }
    }

    if (flag) {
        cout << "Accepts" << endl;
    }
    else {
        cout << "Rejects" << endl;
    }

    return 0;
}