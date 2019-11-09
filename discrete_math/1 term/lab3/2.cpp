#include <iostream>
#include <string>
using namespace std;

void printGray(string binary) {
	string shift = "0", gray = "";
	shift += binary;
	for (int i = 0; i < binary.length(); i++) {
		if (binary[i] != shift[i]) {
			gray += "1";
		}
		else {
			gray += "0";
		}
	}
	cout << gray << endl;
}

void bitString(int x, string prefix) {
	if (x == 0) {
		printGray(prefix);
	}

	else {
		bitString(x - 1, (prefix + "0"));
		bitString(x - 1, (prefix + "1"));
	}
}

int main() {

	freopen("gray.in", "r", stdin);
	freopen("gray.out", "w", stdout);

	int n;
	cin >> n;

	bitString(n, "");

	//system ("pause");
	return 0;
}