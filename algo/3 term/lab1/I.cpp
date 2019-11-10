#include <cmath>
#include <vector>
#include <iostream>
using namespace std;
 
struct Point {
    int x, y;
};
 
double dist(Point first, Point second) {
    return sqrt((first.x - second.x) * (first.x - second.x) + (first.y - second.y) * (first.y - second.y));
}
 
vector<int> endds;
vector<bool> used;
 
// min weight of edges from i
vector<double> distances;
 
vector<Point> points;
 
int main() {
 
    int n;
    cin >> n;
 
    used.resize(n + 1);
    endds.resize(n + 1);
    points.resize(n + 1);
    distances.resize(n + 1);
 
    for (int i = 0; i < n; i++) {
        endds[i] = -1;
        distances[i] = INT32_MAX;
        cin >> points[i].x >> points[i].y;
    }
 
    distances[0] = 0;
    double result = 0;
 
    for (int i = 0; i < n; i++) {
        int min_ind = -1;
        for (int j = 0; j < n; j++) {
            if (!used[j] && (distances[j] < distances[min_ind] || min_ind == -1)) {
                min_ind = j;
            }
        }
 
        used[min_ind] = true;
 
        if (endds[min_ind] != -1) {
            result += dist(points[min_ind], points[endds[min_ind]]);
        }
 
        for (int j = 0; j < n; j++) {
            if (dist(points[min_ind], points[j]) < distances[j]) {
                distances[j] = dist(points[min_ind], points[j]);
                endds[j] = min_ind;
            }
        }
 
    }
 
    printf("%.10f\n", result);
 
    return 0;
}