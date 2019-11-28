#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

string cur_ans;

int main() {

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;
    vector<int> result(n);

    for (int i = 0; i < n; i++) {
        result[i] = i + 1;
    }

    stable_sort(result.begin(), result.end(), [](int a, int b) {
        cout << 1 << ' ' << b << ' ' << a << endl;
        cin >> cur_ans;
        return cur_ans[0] != 'Y';
    });

    cout << 0 << ' ';
    for (int i = 0; i < n; i++) {
        cout << result[i] << ' ';
    }

    return 0;
}