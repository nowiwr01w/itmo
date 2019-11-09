#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
 
string toBinaryString(long long cur) {
    string result;
    do {
        result.push_back('0' + (cur & 1));
    } while (cur >>= 1);
    reverse(result.begin(), result.end());
    return result;
}
 
int main() {
 
    int n;
    cin >> n;
 
    long long result, numbers[5];
    long long try_check = 0, cur_byte = 1;
 
    for (int i = 0; i < n; i++) {
        cin >> numbers[i];
    }
 
    cin >> result;
    string result_string;
    string binary_res = toBinaryString(result);
 
    if (result == 0) {
        cout << "~1&1" << endl;
        return 0;
    }
 
    for (int i = binary_res.length() - 1; i >= 0; i--) {
        if (binary_res[i] == '1') {
            long long cur;
            string cur_string;
            if ((numbers[0] & cur_byte) > 0) {
                cur = numbers[0];
                cur_string.append("1");
            }
            else {
                cur = (~numbers[0]);
                cur_string.append("~1");
            }
            for (int j = 1; j < n; j++) {
                string temp_string;
                if ((numbers[j] & cur_byte) > 0) {
                    cur = cur & numbers[j];
                    temp_string = to_string(j + 1);
                    cur_string.append("&" + temp_string);
                }
                else {
                    cur = cur & ~numbers[j];
                    temp_string = to_string(j + 1);
                    cur_string.append("&~" + temp_string);
                }
            }
            try_check |= cur;
            if (result_string.length() != 0) {
                result_string.append("|");
            }
            result_string.append(cur_string);
        }
        cur_byte = (cur_byte << 1);
    }
 
    if (try_check == result) {
        cout << result_string << endl;
    }
    else {
        cout << "Impossible" << endl;
    }
 
    //system("pause");
    return 0;
}