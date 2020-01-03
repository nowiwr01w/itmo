#include <vector>
#include <iostream>
using namespace std;
 
const uint64_t PRIME = 37;
 
vector<uint64_t> prime;
vector<uint64_t> hashes;
 
uint64_t getHash(int left, int right) {
    return hashes[right + 1] - hashes[left] * prime[right - left + 1];
}
 
int main() {
 
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
 
    string s;
    size_t m;
    size_t a, b, c, d;
 
    cin >> s >> m;
 
    prime.resize(s.length() + 1);
    hashes.resize(s.length() + 1);
 
    prime[0] = 1;
    hashes[0] = 0;
 
    for (size_t i = 0; i < s.length(); i++) {
        prime[i + 1] = prime[i] * PRIME;
        hashes[i + 1] = hashes[i] * PRIME + s[i];
    }
 
    for (size_t i = 0; i < m; i++) {
        cin >> a >> b >> c >> d;
        if (getHash(--a, --b) == getHash(--c, --d)) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
 
    return 0;
}