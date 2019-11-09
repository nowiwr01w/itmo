#include <vector>
#include <iostream>
using namespace std;

int main() {

    cin.tie(0);
    ios_base::sync_with_stdio(0);

    freopen("num2part.in", "r", stdin);
    freopen("num2part.out", "w", stdout);

    int digit, numOfPart;
    cin >> digit >> numOfPart;

    int length = digit - 1;
    vector<int> part(digit, 1);

    while (numOfPart) {
        numOfPart -= 1;
        part[length] -= 1;
        part[length - 1] += 1;
        if (part[length - 1] <= part[length]) {
            while (2 * part[length - 1] <= part[length]) {
                part.push_back(part[length] - part[length - 1]);
                part[length] = part[length - 1];
                length += 1;
            }
        } else {
            part[length - 1] = part[length] + part[length - 1];
            part.pop_back();
            length -= 1;
        }
    }

    for (int i = 0; i <= length; i++) {
        cout << part[i];
        if (i != length) {
            cout << '+';
        }
    }
    cout << endl;
    
    return 0;
}