#include <iostream>
#include <cmath>

using std::cin;
using std::cout;
using std::swap;

const double kInf = 0x3f3f3f3f;
const double kEps = 1e-6;

struct Point {
	double x, y;
};

inline double sq(double a) {
	return a * a;
}

inline double dist(const Point &A, const Point &B) {
	return sqrt(sq(B.x - A.x) + sq(B.y - A.y));
}

inline double isZero(double a) {
	return a < kEps && a > -kEps;
}

inline double isNegative(double a) {
	return a < -kEps;
}

inline double getSlope(const Point &A, const Point &B) {
	if (isZero(B.x - A.x)) {
		return kInf;
	}

	return (B.y - A.y) / (B.x - A.x);
}

inline bool areColinear(const Point &A, const Point &B, const Point &C) {
	return isZero(getSlope(A, B) - getSlope(A, C));
}

inline bool areColinear(const Point &A, const Point &B, const Point &C, const Point &D) {
	return areColinear(A, B, C) && isZero(getSlope(A, B) - getSlope(A, D));
}

inline bool isInf(const double &a) {
	return isZero(a - kInf);
}

int main() {
	Point A, B, C, D;
	cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y >> D.x >> D.y;
	double a = dist(B, C);
	double b = dist(A, C);
	double c = dist(A, B);

	if (areColinear(A, B, C, D)) {
		cout << "A, B, C, D sunt coliniare, deci patrulaterul este circumscriptibil cu cercul de raza infinit.\n";
		return 0;
	}
	else if (areColinear(A, B, C)) {
		cout << "A, B, C sunt coliniare, iar D nu este pe dreapta determinata de ele, deci D este in interiorul " 
			 << "cercului de raza infinit si patrulaterul nu este circumscriptibil.\n";
		return 0;
	}

	double dist_1 = dist(A, B) + dist(C, D);
	double dist_2 = dist(A, D) + dist(B, C);

	if (A.y == B.y) {
		swap(A, C);
	}
	else if (A.y == C.y) {
		swap(A, B);
	}

	const double div_by = sqrt(sq(sq(a) + sq(b) + sq(c)) - 2 * (sq(sq(a)) + sq(sq(b)) + sq(sq(c))));
	const double radius = (div_by != 0) ? a * b * c / div_by : kInf;

	const double m_med_AB = isInf(getSlope(A, B)) ? 0 : -1 / getSlope(A, B);
	const double m_med_AC = isInf(getSlope(A, C)) ? 0 : -1 / getSlope(A, C);

	Point circumcenter = {0, 0};
	circumcenter.x = -((C.y - B.y) - m_med_AC * (A.x + C.x) + m_med_AB * (A.x + B.x)) / (2 * (m_med_AC - m_med_AB));
	circumcenter.y = m_med_AB * circumcenter.x + (A.y + B.y) / 2 - m_med_AB * (A.x + B.x) / 2;

	double diff_D_center = dist(circumcenter, D) - radius;
	// cout << '\n' << radius << ' ' << dist(circumcenter, D) << ' ' << circumcenter.x << ' ' << circumcenter.y << '\n';

	if (isZero(diff_D_center)) {
		cout << "D este pe cerc.\n";
	}
	else if (isNegative(diff_D_center)) {
		cout << "D este in interiorul cercului.\n";
	}
	else {
		cout << "D este in exteriorul cercului.\n";
	}

	if (isZero(dist_1 - dist_2)) {
		cout << "Patrulaterul este circumscriptibil.\n";
	}
	else {
		cout << "Patrulaterul NU este circumscriptibil.\n";
	}
	return 0;
}