#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
 
const int MAX_N = 27;
 
int depth[MAX_N], cur_table[MAX_N];
vector<int> out[MAX_N], edge[MAX_N];
 
int getValue(int ind) {
    int val = 0;
    for (int j : edge[ind]) {
        depth[ind] = max(depth[ind], depth[j] + 1);
        val *= 2;
        val += cur_table[j];
    }
    return val;
}
 
void solve(string &str_table, int n, int ind = 0) {
    if (ind == n) {
        str_table.push_back('0' + cur_table[n - 1]);
    }
    else {
        if (edge[ind].size() > 0) {
            cur_table[ind] = out[ind][getValue(ind)];
            solve(str_table, n, ind + 1);
        }
        else {
            cur_table[ind] = 0;
            solve(str_table, n, ind + 1);
            cur_table[ind] = 1;
            solve(str_table, n, ind + 1);
        }
    }
}
 
int main() {
 
    int n, m;
    string ans_vals;
 
    cin >> n;
 
    for (int i = 0; i < n; i++) {
        cin >> m;
        if (m == 0) {
            continue;
        }
 
        int temp;
        for (int j = 0; j < m; j++) {
            cin >> temp;
            edge[i].push_back(temp - 1);
        }
 
        for (int j = 0; j < pow(2, m); j++) {
            cin >> temp;
            out[i].push_back(temp);
        }
    }
 
    solve(ans_vals, n);
    cout << depth[n - 1] << endl << ans_vals << endl;
 
    //system("pause");
    return 0;
}