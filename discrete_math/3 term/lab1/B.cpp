#include <deque>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    freopen("chvatal.in", "r", stdin);
    freopen("chvatal.out", "w", stdout);

    int n;
    string nn;
    getline(cin, nn);
    n = stoi(nn);

    deque<int> queue;
    vector<vector<int>> graph(n + 1, vector<int>(n + 1, 0));

    for (int i = 1; i < n + 1; i++) {
        string buffer;
        getline(cin, buffer);
        int position = 1;
        queue.push_back(i);
        for (char j : buffer) {
            graph[i][position] = graph[position][i] = (j == '1');
            position += 1;
        }
    }

    for (int k = 0; k < n * (n - 1); k++) {
        int first = queue[0];
        int second = queue[1];
        if (graph[first][second] == 0) {
            int j = 2;
            while (j < n - 1 && (graph[first][queue[j]] == 0 || graph[second][queue[j + 1]] == 0)) {
                j += 1;
            }
            if (j == n - 1) {
                j = 2;
                while (j < n && graph[first][queue[j]] == 0) {
                    j += 1;
                }
            }
            reverse(queue.begin() + 1, queue.begin() + j + 1);
        }
        queue.pop_front();
        queue.push_back(first);
    }

    for (auto i : queue) {
        cout << i << ' ';
    }

    return 0;
}