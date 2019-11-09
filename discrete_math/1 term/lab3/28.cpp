#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void nextMultiset(vector<int> current_set) {

	int n = current_set.size();
	int check = current_set.size() - 2;

	while (check >= 0 && current_set[check] >= current_set[check + 1]) {
		check -= 1;
	}

	if (check < 0) {
		for (int i = 0; i < n; i++) {
			cout << "0 ";
		}
	}
	else {

		int j = check + 1;
		while (j < n - 1 && current_set[j + 1] > current_set[check]) {
			j += 1;
		}

		swap(current_set[check], current_set[j]); 

		int num_steps = (n - 1 - (check + 1)) / 2 + 1;

		for (int j = 0; j < num_steps; j++) {
			swap(current_set[check + 1 + j], current_set[n - 1 - j]);
		}

		for (int j = 0; j < n; j++) {
			cout << current_set[j] << " ";
		}
	}
} 

int main() {

	cin.tie(nullptr);
    	ios_base::sync_with_stdio(false);

    	freopen("nextmultiperm.in", "r", stdin);
    	freopen("nextmultiperm.out", "w", stdout);

	int n;
	cin >> n;

	vector<int> result(n);

	for (int i = 0; i < n; i++) {
		cin >> result[i];
	}

	nextMultiset(result);

	//system("pause");
	return 0;
}