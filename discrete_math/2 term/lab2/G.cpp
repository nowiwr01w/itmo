#include <map>
#include <queue>
#include <vector>
#include <iostream>	
#include <algorithm>
using namespace std;

const int MAXN = 100001;

int aut1[MAXN][26];
int aut2[MAXN][26];

bool term1[MAXN];
bool term2[MAXN];
bool visited1[MAXN];
bool visited2[MAXN];

bool bfs(queue<pair<int, int>> current_queue) {
	pair<int, int> temp = make_pair(1, 1);
	current_queue.push(temp);
	while (!current_queue.empty()) {
		pair<int, int> new_cur = current_queue.front();
		if (new_cur.first != 0) {
			visited1[new_cur.first] = true;
		}
		if (new_cur.second != 0) {
			visited2[new_cur.second] = true;
		}
		current_queue.pop();
		if (term1[new_cur.first] != term2[new_cur.second]) {
			return false;
		}
		for (int i = 0; i < 26; i++) {
			int u = aut1[new_cur.first][i];
			int v = aut2[new_cur.second][i];
			if (visited1[u] == false || visited2[v] == false) {
				if (v != 0 || u != 0) {
					current_queue.push(make_pair(u, v));
				}
			}
		}
	}
	return true;
}

int main() {

	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);
	freopen("equivalence.in", "r", stdin);
	freopen("equivalence.out", "w", stdout);

	char symbol;
	int a, b, t;
	int n, m, k;
	int n1, m1, k1;
	queue<pair<int, int>> current_queue;

	cin >> n >> m >> k;

	for (int i = 0; i < MAXN; i++) {
		term1[i] = term2[i] = false;
		visited1[i] = visited2[i] = false;
		for (int j = 0; j < 30; j++) {
			aut1[i][j] = aut2[i][j] = 0;
		}
	}

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