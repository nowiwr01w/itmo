#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

double f(double x, double c) {
	return x * x + sqrt(x) - c;
}

void bisection(double a, double b, double x, double eps = 0.000000001) {
	double c = a;
	while ((b - a) >= eps) {
		c = (a + b) / 2;
		if (f(c, x) * f(a, x) < 0) {
			b = c;
		}
		else {
			a = c;
		}
	}
	cout << c << endl;
}

int main() {

	double c;
	double a = 0, b = 10000000001;

	cin >> c;
	cout.precision(7);
	bisection(a, b, c);

	//system("pause");
	return 0;
}