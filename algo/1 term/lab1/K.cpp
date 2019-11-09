#include <math.h>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<pair<pair<double, double>, int>> cur;
vector<pair<pair<double, double>, int>> temp;

bool assign(double x, int n, int k) {
	for (int i = 0; i < n; i++) {
		temp[i].second = i + 1;
		temp[i].first.first = cur[i].first.first - x * cur[i].first.second;
	}
	double sum = 0;
	sort(temp.begin(), temp.end());
	reverse(temp.begin(), temp.end());
	for (int i = 0; i < k; i++) {
		sum += temp[i].first.first;
	}
	return sum >= 0 ? true : false;
}

void binSearch(double eps, int n, int k) {
	double left = 0, right = 10000001;
	while (abs(right - left) > eps) {
		double middle = (left + right) / 2;
		if (assign(middle, n, k)) {
			left = middle;
		}
		else {
			right = middle;
		}
	}
	vector<int> results(k, -1);
	for (int i = 0; i < k; i++) {
		results[i] = temp[i].second;
	}
	sort(results.begin(), results.end());
	for (int i = 0; i < k; i++) {
		cout << results[i] << endl;
	}
}

int main() {

	cin.tie(0);
	ios_base::sync_with_stdio(0);
	freopen("kbest.in", "r", stdin);
	freopen("kbest.out", "w", stdout);

	double t;
	int n, k;
	double x, y;
	cin >> n >> k;

	cur.resize(n);
	temp.resize(n);

	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		cur[i].second = i + 1;
		cur[i].first = make_pair(x, y);
	}

	binSearch(0.000000001, n, k);

	//system("pause");
	return 0;
}