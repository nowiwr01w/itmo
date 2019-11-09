#include <map>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

vector<string> chainCode(int n) {
	string current = "";
	map<string, int> cur_map;
	for (int i = 0; i < n; i++) {
		current += '0';
	}
	cur_map[current] = 1;
	vector<string> cur_vec{ current };
	while (true) {
		string prefix = current.substr(1);
		string cur_prefix = prefix + '1';
		string cur_prefix1 = prefix + '0';
		if (cur_map[cur_prefix] == 0) {
			current = cur_prefix;
		}
		else if (cur_map[cur_prefix1] == 0) {
			current = cur_prefix1;
		}
		else {
			break;
		}
		cur_map[current] = 1;
		cur_vec.push_back(current);
	}
	return cur_vec;
}

int main() {

	freopen("chaincode.in", "r", stdin);
	freopen("chaincode.out", "w", stdout);

	cin.tie(0);
	ios_base::sync_with_stdio(0);

	int n;
	cin >> n;

	vector<string> a = chainCode(n);

	for (int i = 0; i < a.size(); i++) {
		cout << a[i] << endl;
	}

	//system("pause");
	return 0;
}