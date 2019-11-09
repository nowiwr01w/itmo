#include <vector>
#include <string>
#include <iostream>
using namespace std;

void getPrev(vector<int> &a, string s) {
	int n = s.length() - 1;
	while (n >= 0 && a[n] != 1) {
		a[n] = 1;
		n -= 1;
	}
	if (n == -1) {
		cout << "-" << endl;
		return;
	}
	a[n] = 0;
	for (int i = 0; i < s.length(); i++) {
		cout << a[i];
	}
	cout << endl;
}

void getNext(vector<int> &b, string s) {
	int n1 = s.length() - 1;
	while (n1 >= 0 && b[n1] != 0) {
		b[n1] = 0;
		n1 -= 1;
	}
	if (n1 == -1) {
		cout << "-" << endl;
		return;
	}
	b[n1] = 1;
	for (int i = 0; i < s.length(); i++) {
		cout << b[i];
	}
	cout << endl;
}

int main() {

	cin.tie(0);
	ios::sync_with_stdio(false);
	freopen("nextvector.in", "r", stdin);
	freopen("nextvector.out", "w", stdout);

	string s;
	vector<int> a;
	vector<int> b;

	cin >> s;

	for (int i = 0; i < s.length(); i++) {
		a.push_back(s[i] - '0');
		b.push_back(s[i] - '0');
	}

	getPrev(b, s);
	getNext(a, s);
	
	//system("pause");
	return 0;
}