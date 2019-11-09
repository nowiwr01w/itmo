#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

long long binarySearch(vector<long long> &a, long long key, int n) {
	long long l = -1, r = n;
	while (l < r - 1) {
		long long m = (l + r) / 2;
		if (a[m] < key) {
			l = m;
		}
		else {
			r = m;
		}
	}
	return r;
}

long long binarySearchOne(vector<long long> &a, long long key, int n) {
	long long l = -1, r = n;
	while (l < r - 1) {
		long long m = (l + r) / 2;
		if (a[m] <= key) {
			l = m;
		}
		else {
			r = m;
		}
	}
	return r;
}

int main() {

	cin.tie(0);
	ios_base::sync_with_stdio(0);

	long long x, y;
	long long n, k;

	cin >> n;
	vector<long long> arr(n, 0);

	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	sort(arr.begin(), arr.end());

	cin >> k;
	for (int i = 0; i < k; i++) {
		cin >> x >> y;
		long long first = binarySearch(arr, x, n);
		long long second = binarySearchOne(arr, y, n);
		cout << abs(first - second) << endl;
	}

	//system("pause");
	return 0;
}