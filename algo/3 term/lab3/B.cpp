#include <vector>
#include <string>
#include <iostream>
using namespace std;
 
void calculatePrefixFunction(vector<uint64_t> &prefixFunction, const string &input) {
    for (size_t i = 1; i < input.length(); i++) {
        uint64_t j = prefixFunction[i - 1];
        while (j > 0 && input[i] != input[j]) {
            j = prefixFunction[j - 1];
        }
        if (input[i] == input[j]) {
            j++;
        }
        prefixFunction[i] = j;
    }
}
 
int main() {
 
    string input;
    cin >> input;
 
    vector<uint64_t> prefixFunction(input.length());
    calculatePrefixFunction(prefixFunction, input);
 
    for (uint64_t item : prefixFunction) {
        cout << item << " ";
    }
 
    return 0;
}