#include <string>
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

bool isOperand(char symbol) {
	return symbol == '+' || symbol == '-' || symbol == '*';
}

void getResult(vector<long long> &vec, string a) {
	if (vec.size() >= 2) {
		long long int r = vec.back();
		vec.pop_back();
		long long int l = vec.back();
		vec.pop_back();

		switch (a[0]) {
		case '+':
			vec.push_back(l + r);
			break;
		case '-':
			vec.push_back(l - r);
			break;
		case '*':
			vec.push_back(l * r);
			break;
		default:
			vec.push_back(stoi(a));
		}
	}
	else {
		vec.push_back(stoi(a));
	}
}

int main() {

	cin.tie(0);
	ios_base::sync_with_stdio(0);

	string input, new_string;
	vector<long long> new_stack;

	getline(cin, new_string);
	stringstream stream(new_string);

	while (stream >> input) {
		if (isOperand(input[0]) && input.length() == 1)
			getResult(new_stack, input);
		else
			new_stack.push_back(stoll(input));
	}

	cout << new_stack.back() << endl;

	//system("pause");
	return 0;
}