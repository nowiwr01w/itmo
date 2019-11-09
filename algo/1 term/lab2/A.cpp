#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <iostream>
using namespace std;

int main() {

	cin.tie(0);
	ios_base::sync_with_stdio(0);

	long long n;
	scanf("%I64d", &n);
	vector<long long> first;
	vector<long long> second;
	long long min_elem = 100000 * 10000 + 1;

	for (int i = 0; i < n; i++) {
		long long x;
		scanf("%I64d", &x);
		if (x == 1) {
			long long y;
			scanf("%I64d", &y);
			first.push_back(y);
			if (y <= min_elem) {
				min_elem = y;
				second.push_back(y);
			}
			else {
				second.push_back(min_elem);
			}
		}
		if (x == 2) {
			second.pop_back();
			if (second.size() > 0) {
				min_elem = second[second.size() - 1];
			}
			else {
				min_elem = 100000 * 10000 + 1;
			}
			first.pop_back();
		}
		if (x == 3) {
			cout << second[second.size() - 1] << endl;
		}
	}

	//system("pause");
	return 0;
}