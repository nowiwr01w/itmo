#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    
        cin.tie(0);
        ios_base::sync_with_stdio(0);

        freopen("permutations.in", "r", stdin);
        freopen("permutations.out", "w", stdout);

        int length;
        cin >> length;

        vector<int> cur_vec(9, 0);

        for(int i = 0; i < length; i++) {
            cur_vec[i] = i + 1;
        }

        if (length == 1) { 
          cout << 1 << endl; 
          return 0;
        }

        int i = length - 2;

        for (int j = 0; j < length; j++) {
            cout << cur_vec[j] << " ";
        }
        cout << endl;

        while (true) {
            if (cur_vec[i] < cur_vec[i + 1]) {
                for (int m = length - 1; m > i; m--) {
                    if (cur_vec[i] < cur_vec[m]) {
                        swap(cur_vec[i], cur_vec[m]);
                        reverse(cur_vec.begin() + i + 1, cur_vec.begin() + length);
                        i = length - 1;
                        for (int i = 0; i < length; i++) {
                            cout << cur_vec[i]<< " ";
                        }
                        cout << endl;
                        break;
                    }
                }
            }

            i -= 1;
            if (i == -1) { 
              break;
            }

        }

        //system("pause");
        return 0;
}