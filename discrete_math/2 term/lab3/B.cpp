#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1001;

bool is_eps[MAXN];
bool already_eps[MAXN];

vector<string> eps_not_terminals;
vector<pair<string, string>> rules;


int main() {

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    freopen("epsilon.in", "r", stdin);
    freopen("epsilon.out", "w", stdout);

    int n;
    char first;
    bool added = true;
    string s1, s2, s3;

    cin >> n >> first;

    for (int i = 0; i < n; ++i) {
        cin >> s1;
        if (s1 == "->") {
            cin >> s3;
            s1 = rules[rules.size() - 1].second;
            rules[rules.size() - 1].second = "";
        } else {
            cin >> s2 >> s3;
        }
        rules.emplace_back(s1, s3);
    }

    while (added) {
        bool added_now = false;
        for (int i = 0; i < n; i++) {
            if (already_eps[i]) {
                continue;
            }
            pair<string, string> rule = rules[i];
            string right = rule.second;
            bool new_eps = true;
            for (char j : right) {
                if (!is_eps[j]) {
                    new_eps = false;
                    break;
                }
            }
            if (new_eps) {
                eps_not_terminals.push_back(rule.first);
                added_now = already_eps[i] = is_eps[rule.first[0]] = true;
            }
        }
        added = added_now;
    }

    sort(eps_not_terminals.begin(), eps_not_terminals.end());

    for (const auto &eps_not_terminal : eps_not_terminals) {
        cout << eps_not_terminal << ' ';
    }

    return 0;
}