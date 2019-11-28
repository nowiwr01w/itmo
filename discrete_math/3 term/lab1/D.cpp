#include <random>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAX_N = 1001;

vector<int> res;
vector<vector<bool>> graph;

int comp(int a, int b) {
    return graph[a][b];
}

int main() {

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    freopen("guyaury.in", "r", stdin);
    freopen("guyaury.out", "w", stdout);

    int n;
    char sym;

    cin >> n;

    res.resize(MAX_N);
    graph.resize(MAX_N, vector<bool>(MAX_N));

    for (int i = 0; i < n; i++) {
        res[i] = i + 1;
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            cin >> sym;
            graph[i + 1][j + 1] = sym == '1';
            graph[j + 1][i + 1] = sym != '1';
        }
    }

    while (true) {
        shuffle(res.begin(), res.begin() + n, std::mt19937(std::random_device()()));
        sort(res.begin(), res.begin() + n, comp);
        if (graph[res[n - 1]][res[0]]) {
            break;
        }
    }

    for (int i = 0; i < n; i++) {
        cout << res[i] << " ";
    }

    return 0;
}