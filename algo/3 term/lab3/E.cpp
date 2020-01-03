#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
 
vector<size_t> calculateZFunction(const string &input) {
    vector<size_t> zFunction(input.length(), 0);
    size_t l = 0;
    size_t r = 0;
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
    return zFunction;
}
 
size_t findLengthOfPeriod(const string& input) {
    size_t period = input.size();
    size_t input_size = input.size();
    vector<size_t> zFunction = calculateZFunction(input);
    for (size_t i = 1; i < input_size; i++) {
        if (input_size % i == 0 && input_size - i == zFunction[i]) {
            period = i;
            break;
        }
    }
    return period;
}
 
 
int main() {
 
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
 
    string input;
    cin >> input;
 
    cout << findLengthOfPeriod(input);
 
    return 0;
}