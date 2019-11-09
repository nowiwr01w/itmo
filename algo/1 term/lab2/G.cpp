#include <string>
#include <vector>
#include <iostream>
using namespace std;

#define MAX_N 300001

struct params {
	int min;
	int max;
	int count;
};

int parent[MAX_N];
int cur_rank[MAX_N];
vector<params> cur_vec(MAX_N);

int findSet(int vertex) {
	if (vertex == parent[vertex]) {
		return vertex;
	}
	return parent[vertex] = findSet(parent[vertex]);
}

void get(int root) {
	int root1 = findSet(root);
	cout << cur_vec[root1].min << " " << cur_vec[root1].max << " " << cur_vec[root1].count << endl;
}

void makeSet(int vertex) {
	parent[vertex] = vertex;
	cur_rank[vertex] = 1;
	cur_vec[vertex].min = vertex;
	cur_vec[vertex].max = vertex;
	cur_vec[vertex].count = 1;
}

void union_(int first, int second) {
	first = findSet(first);
	second = findSet(second);
	if (first != second) {
		if (cur_rank[first] < cur_rank[second]) {
			swap(first, second);
		}
		parent[second] = first;
		cur_rank[first] += cur_rank[second];
		cur_vec[first].count = cur_rank[first];
		if (cur_vec[first].max < cur_vec[second].max) {
			cur_vec[first].max = cur_vec[second].max;
		}
		if (cur_vec[first].min > cur_vec[second].min) {
			cur_vec[first].min = cur_vec[second].min;
		}
	}
}

int main() {

	int n;
	cin >> n;
	string s;

	for (int i = 1; i <= n; i++) {
		makeSet(i);
	}

	while (cin >> s) {
		int x;
		cin >> x;
		if (s[0] == 'g') {
			get(x);
		}
		if (s[0] == 'u') {
			int b;
			cin >> b;
			union_(x, b);
		}
	}

	//system("pause");
	return 0;
}