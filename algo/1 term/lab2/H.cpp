#include <vector>
#include <iostream>
#include <string>
using namespace std;

struct user {
	int prev, rang, exp, diff;
	user(int v = 0) {
		prev = v;
		rang = 0;
		exp = 0;
		diff = 0;
	}
};

vector<user> cur_vec;

int get(int x) {
	int t = cur_vec[x].prev;
	if (cur_vec[x].prev != x) {
		cur_vec[x].prev = get(cur_vec[x].prev);
	}
	cur_vec[x].diff += cur_vec[t].diff;
	return cur_vec[x].prev;
}

void merge(int x, int y) {
	x = get(x);
	y = get(y);
	if (x == y) {
		return;
	}
	if (cur_vec[x].rang == cur_vec[y].rang) {
		cur_vec[x].rang++;
	}
	if (cur_vec[x].rang < cur_vec[y].rang) {
		cur_vec[x].prev = y;
		cur_vec[x].diff = cur_vec[x].exp - cur_vec[y].exp;
	}
	else {
		cur_vec[y].prev = x;
		cur_vec[y].diff = cur_vec[y].exp - cur_vec[x].exp;
	}
}

int main() {

	int n, m;
	int x, y;
	string s;
	cin >> n >> m;

	cur_vec.resize(n);

	for (int i = 0; i < n; i++) {
		cur_vec[i] = user(i);
	}

	for (int i = 0; i < m; i++) {
		cin >> s;
		if (s[0] == 'j') {
			cin >> x >> y;
			merge(x - 1, y - 1);
		}
		if (s[0] == 'g') {
			cin >> x;
			cout << cur_vec[get(x - 1)].exp + cur_vec[x - 1].diff << endl;
		}
		if (s[0] == 'a') {
			cin >> x >> y;
			cur_vec[get(x - 1)].exp += y;
		}
	}

	//system("pause");
	return 0;
}