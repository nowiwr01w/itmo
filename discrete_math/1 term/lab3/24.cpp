#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

vector<long long> prevPermutation(vector<long long> cur_vec) {
    long long max = -1, length = cur_vec.size();
    for (long long i = cur_vec.size() - 2; i >= 0; i--) {
        if (cur_vec[i] > cur_vec[i + 1]) {
            max = i + 1;
            for (long long j = i + 1; j < cur_vec.size(); j++) {
                if (cur_vec[j] > cur_vec[max] && cur_vec[j] < cur_vec[i]) {
                    max = j;
                }
            }
            swap(cur_vec[i], cur_vec[max]);
            reverse(cur_vec.begin() + i + 1, cur_vec.end());
            return cur_vec;
        }

    }
    vector<long long> k(length, 0);
    return k;
}

vector<long long> nextPermutation(vector<long long> cur_vec) {
    long long min = 100001, length = cur_vec.size();
    for (long long i = length - 2; i >= 0; i--) {
        if (cur_vec[i] < cur_vec[i + 1]) {
            min = i + 1;
            for (long long j = i + 1; j < length; j++) {
                if (cur_vec[i] < cur_vec[j] && cur_vec[min] > cur_vec[j]) {
                    min = j;
                }
            }
            swap(cur_vec[i], cur_vec[min]);
            reverse(cur_vec.begin() + i + 1, cur_vec.end());
            return cur_vec;
        }

    }
    vector<long long> k(length, 0);
    return k;
}

int main() {

    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    freopen("nextperm.in", "r", stdin);
    freopen("nextperm.out", "w", stdout);

    long long n;
    cin >> n;
    vector<long long> cur_vec(n, 0);

    for (long long i = 0; i < n; i++) {
        cin >> cur_vec[i];
    }

    vector<long long> result_next = nextPermutation(cur_vec);
    vector<long long> result_prev = prevPermutation(cur_vec);

    for (long long i : result_prev) {
        cout << i << " ";
    }

    cout << endl;

    for (long long i : result_next) {
        cout << i << " ";
    }

    return 0;
}