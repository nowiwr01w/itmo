#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
 
void calculateZFunction(vector<uint64_t> &zFunction, const string &input) {
    uint64_t l = 0;
    uint64_t r = 0;
    for (size_t i = 1; i < input.length(); i++) {
        if (i <= r) {
            zFunction[i] = min(r - i + 1, zFunction[i - l]);
        }
        while (i + zFunction[i] < input.length() && input[zFunction[i]] == input[i + zFunction[i]]) {
            zFunction[i] += 1;
        }
        if (i + zFunction[i] - 1 > r) {
            l = i;
            r = i + zFunction[i] - 1;
        }
    }
}
 
int main() {
 
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
 
    string input;
    cin >> input;
 
    vector<uint64_t> zFunction(input.length());
    calculateZFunction(zFunction, input);
 
    for (size_t i = 1; i < zFunction.size(); i++) {
        cout << zFunction[i] << " ";
    }
 
    return 0;
}