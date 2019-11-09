#include <vector>
#include <iostream>
using namespace std;

int find(vector<int> &a, int elem) {
	for (int i = 0; i < a.size(); i++) {
		if (a[i] == elem) {
			return i;
		}
	}
}

int main() {

	int n, x, y;
	int startIndex = 0;
		
	cin >> n;
	vector<int> a;

	for (int i = 0; i < n; i++) {
		cin >> x;
		if (x == 1) {
			cin >> y;
			a.push_back(y);
		}
		if (x == 2) {
			startIndex++;
		}
		if (x == 3) {
			a.pop_back();
		}
		if (x == 4) {
			cin >> y;
			cout << find(a, y) - startIndex << endl;
		}
		if (x == 5) {
			cout << a[startIndex] << endl;
		}
	}

	//system("pause");
	return 0;
}