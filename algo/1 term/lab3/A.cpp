#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <iterator>
using namespace std;
 
int main() {
 
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
 
    int n, k, jump = 0;
    string new_string = "";
    cin >> n >> k;
    int ind = n - 1;
    vector<long long> count_money(n, 0);
    vector<long long> summa(n, 0);
    vector<long long> prev(n, -1);
    for (int i = 1; i < n - 1; i++) {
        cin >> count_money[i];
    }
    for (int i = 1; i < n; i++) {
        summa[i] = summa[i - 1] + count_money[i];
        prev[i] = i - 1;
        for (int j = 2; j <= min(i, k); j++) {
            if (summa[i] < summa[i - j] + count_money[i]) {
                summa[i] = summa[i - j] + count_money[i];
                prev[i] = i - j;
            }
        }
    }
    while (ind >= 0) {
        new_string += to_string(ind + 1);
        if (ind != 0) {
            new_string += " ";
            jump += 1;
        }
        ind = prev[ind];
    }
    istringstream buf(new_string);
    istream_iterator<string> beg(buf), end;
    vector<string> res_array(beg, end);
    new_string = "";
    for (int j = res_array.size() - 1; j >= 0; j--) {
        new_string += res_array[j];
        if (j > 0) {
            new_string += " ";
        }
    }
 
    cout << summa[n - 1] << endl;
    cout << jump << endl;
    cout << new_string;
 
    return 0;
}