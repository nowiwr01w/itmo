#include <iostream>
#include <string>
#include <vector>
using namespace std;

void generate(int n, int open, int close, string &prefix) {
	if (open + close == n) {
		cout << prefix << endl;
	}
	else {
		if (open < n / 2) {
			prefix.push_back('(');
			generate(n, open + 1, close, prefix);
			prefix.pop_back();
		}
		if (close < open) {
			prefix.push_back(')');
			generate(n, open, close + 1, prefix);
			prefix.pop_back();
		}
	}
}

int main() {
	
	cin.tie(0);
      	ios_base::sync_with_stdio(0);
  
  	freopen("brackets.in", "r", stdin);
  	freopen("brackets.out", "w", stdout);


	int n;
	cin >> n;
	string res = "";

	generate(2 * n, 0, 0, res);

	//system("pause");
	return 0;
}