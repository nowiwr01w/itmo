#include <deque>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

// https://vk.cc/a2xwg2 - description of solution

int main() {

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    freopen("fullham.in", "r", stdin);
    freopen("fullham.out", "w", stdout);

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
        auto start = queue.begin();
        if (graph[*start][*(start + 1)] == 0) {
            int i = 2;
            while (graph[*start][*(start + i)] == 0 || graph[*(start + 1)][*(start + i + 1)] == 0) {
                i += 1;
            }
            reverse(start + 1, start + i + 1);
        }
        queue.push_back(queue.front());
        queue.pop_front();
    }

    for (int i : queue) {
        cout << i << ' ';
    }

    return 0;
}