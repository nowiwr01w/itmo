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
	return l;
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

	long long n, k;
	cin >> n >> k;

	vector<long long> arr(n, 0);
	vector<long long> check(k, 0);

	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	for (int i = 0; i < k; i++) {
		cin >> check[i];
		long long first = binarySearch(arr, check[i], n);
		first = max(first, (long long) 0);
		long long second = binarySearchOne(arr, check[i], n);
		second = min(second, n - 1);
		long long third = binarySearch(arr, check[i], n);
		third += 1;
		third = min(third, n - 1);
		if (arr[third] != check[i]) {
			if (abs(arr[first] - check[i]) <= abs(arr[second] - check[i])) {
				cout << arr[first] << endl;
			}
			else {
				cout << arr[second] << endl;
			}
		}
		else {
			cout << arr[third] << endl;
		}		
	}

	//system("pause");
	return 0;
}