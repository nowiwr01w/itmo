#include <deque>
#include <vector>
#include <iostream>
using namespace std;

int main() {

	cin.tie(0);
	ios_base::sync_with_stdio(0);

	int n, x;
	char symbol;
	deque<int> first_half;
	deque<int> second_half;

	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> symbol;
		if (symbol == '+') {
			cin >> x;
			second_half.push_back(x);
		}
		if (symbol == '-') {
			cout << first_half.front() << endl;
			first_half.pop_front();
		}
		if (symbol == '*') {
			cin >> x;
			second_half.push_front(x);
		}
		while (first_half.size() < second_half.size()) {
			first_half.push_back(second_half.front());
			second_half.pop_front();
		}
	}

	//system("pause");
	return 0;
}