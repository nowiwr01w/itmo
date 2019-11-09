#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

long long inv_cnt = 0;

void mergeLists(vector<int> &a, int left, int middle, int right) {
	int it1 = 0, it2 = 0;
	vector<int> result(right - left + 1, 0);
	while ((left + it1 < middle) && (middle + it2 <= right)) {
		if (a[left + it1] <= a[middle + it2]) {
			result[it1 + it2] = a[left + it1];
			it1 += 1;
		}
		else {
			inv_cnt += middle - (left + it1);
			result[it1 + it2] = a[middle + it2];
			it2 += 1;
		}
	}
	while (left + it1 < middle) {
		result[it1 + it2] = a[left + it1];
		it1 += 1;
	}
	while (middle + it2 <= right) {
		result[it1 + it2] = a[middle + it2];
		it2 += 1;
	}
	for (int i = 0; i < it1 + it2; i++) {
		a[left + i] = result[i];
	}
}

void mergeSort(vector<int> &a, int left, int right) {
	if (left >= right) {
		return;
	}
	int middle = (left + right) / 2;
	mergeSort(a, left, middle);
	mergeSort(a, middle + 1, right);
	mergeLists(a, left, middle + 1, right);
}

int main() {

	int n; 
	cin >> n;
	vector<int> a(n, 0);

	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	mergeSort(a, 0, n - 1);

	cout << inv_cnt << endl;

	//system("pause");
	return 0;
}