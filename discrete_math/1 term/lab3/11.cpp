#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<vector<int>> getSubSet(vector<int> element) {
	int length = 1 << element.size();
	vector<vector<int>> vector_result;
	for (int binary = 0; binary < length; binary++) {
		vector<int> sub_vector;
		for (int bit = 0; bit < element.size(); bit++) {
			int mask = 1 << bit;
			if ((binary & mask) != 0) {
				sub_vector.push_back(element[bit]);
			}
		}
		vector_result.push_back(sub_vector);
	}
	return vector_result;
}

int main() {

    	cin.tie(0);
    	ios_base::sync_with_stdio(0);

    	freopen("subsets.in", "r", stdin);
    	freopen("subsets.out", "w", stdout);

	int n;
	cin >> n;
	vector<int> current_numbers(n, 0);

	for (int i = 0; i < n; i++) {
		current_numbers[i] = i + 1;
	}
 
	vector<vector<int>> result = getSubSet(current_numbers);

	sort(result.begin(), result.end());

	for (vector<int> res : result) {
		for (int element : res) {
			cout << element << " ";
		}
		cout << endl;
	}

	//system("pause");
	return 0;
}