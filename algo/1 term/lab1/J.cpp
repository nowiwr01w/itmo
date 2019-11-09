#include <cmath>
#include <iostream>
using namespace std;

double f(double x, double a, double p, double q) {
	return (sqrt((1 - a) * (1 - a) + x * x)) / p + (sqrt(a * a + (1 - x) * (1 - x))) / q;
}

double tern(double left, double right, double c, double p, double q, double eps) {
	if (right - left < eps) {
		return (left + right) / 2;
	}

	double a = (left * 2 + right) / 3;
	double b = (left + 2 * right) / 3;

	if (f(a, c, p, q) < f(b, c, p, q)) {
		return tern(left, b, c, p, q, eps);
	}
	else {
		return tern(a, right, c, p, q, eps);
	}
}

int main() {

	double EPS = 0.0000001;
	double a, p, q;
	double left = 0, right = 1;

	cin >> p >> q >> a;

	cout.precision(5);
	cout << tern(left, right, a, p, q, EPS) << endl;

	//system("pause");
	return 0;
}