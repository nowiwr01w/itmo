#include <vector>
#include <iostream>
using namespace std;
 
vector<uint64_t> prefixFunction(const string& input) {
    vector<uint64_t> prefixFunction(input.length());
    prefixFunction[0] = 0;
    for (size_t i = 1; i < input.length(); ++i) {
        uint64_t j = prefixFunction[i - 1];
        while (j > 0 && input[i] != input[j]) {
            j = prefixFunction[j - 1];
        }
        if (input[i] == input[j]) {
            ++j;
        };
        prefixFunction[i] = j;
    }
    return prefixFunction;
}
 
vector<uint64_t> KMP(const string& pattern, const string& text) {
    size_t inputSize = text.length();
    size_t prefixSize = pattern.length();
    vector<uint64_t> result;
    vector<uint64_t> prefix = prefixFunction(pattern + "#" + text);
    for (size_t i = prefixSize; i < prefixSize + 1 + inputSize; ++i) {
        if (prefix[i] == prefixSize) {
            result.push_back(i - prefixSize * 2 + 1);
        }
    }
    return result;
}
 
int main() {
 
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
 
    string prefix, input;
    cin >> prefix >> input;
 
    vector<uint64_t> res = KMP(prefix, input);
 
    cout << res.size() << endl;
    for (uint64_t item : res) {
        cout << item << " ";
    }
 
    return 0;
}