#include <map>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

const int MAXN = 1001;

bool check(vector<pair<int, int>> graph[MAXN], string current_string, int position, int vertex) {
    if (position == current_string.size()) {
        return vertex == -1;
    }
    if (vertex == -1) {
        return false;
    }
    int charInt = current_string[position] - 'a';
    for (pair<int, int> to : graph[vertex]) {
        if (to.first == charInt) {
            if (check(graph, current_string, position + 1, to.second)) {
                return true;
            }
        }
    }
    return false;
}


int main() {
    
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    freopen("cf.in", "r", stdin);
    freopen("cf.out", "w", stdout);

    int n, m;
    char symbol;
    string current_string;
    vector<pair<int, int>> graph[MAXN];

    cin >> n >> symbol;

    getline(cin, current_string);
    for (int i = 0; i < n; i++) {
        getline(cin, current_string);
        int position = 0;
        while (current_string[position] < 'A' || current_string[position] > 'Z') {
            position += 1;
        }

        int from = current_string[position] - 'A';
        position += 1;

        while (current_string[position] < 'a' || current_string[position] > 'z') {
            position++;
        }
        int to = -1;
        int terminal = current_string[position] - 'a';
        position += 1;

        if (position < current_string.size()) {
            to = current_string[position] - 'A';
        }
        graph[from].emplace_back(terminal, to);
    }

    cin >> m;
    getline(cin, current_string);

    for (int i = 0; i < m; i++) {
        getline(cin, current_string);
        if (check(graph, current_string, 0, symbol - 'A')) {
            cout << "yes" << endl;
        }
        else {
            cout << "no" << endl;
        }
    }

    return 0;
}