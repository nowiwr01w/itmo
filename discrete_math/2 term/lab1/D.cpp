#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
	freopen("markchain.in", "r", stdin);
	freopen("markchain.out", "w", stdout);

    unsigned int n;
    
    cin >> n;
    vector<vector<double>> oldMatrix(n, vector<double>(n));
    vector<vector<double>> newMatrix(n, vector<double>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> oldMatrix[i][j];
        }
    }

    for (int k = 0; k < 1000000; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int z = 0; z < n; z++) {
                    newMatrix[i][j] += oldMatrix[i][z] * oldMatrix[z][j];
                }
            }
        }
        // Меняем матрицы местами
        double difference = 0.0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                difference = max(difference, abs(oldMatrix[i][j] - newMatrix[i][j]));
                oldMatrix[i][j] = newMatrix[i][j];
                newMatrix[i][j] = 0;
            }
        }
        if (difference < 0.00001) {
            break;
        }
    }

    cout.precision(6);
    cout.setf(ios::fixed | ios::showpoint);

    for (int i = 0; i < n; i++) {
        cout << oldMatrix[0][i] << endl;
    }

    return 0;
}