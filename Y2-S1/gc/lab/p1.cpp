/*
Fie Ai(xi, yi, zi) in R^3, i in {1..3}
a) Sa se decida daca cele 3 puncte sunt coliniare
b) In caz afirmativ, exprimati unul dintre punctee ca o combinatie afina a celorlalte 2
*/

#include <iostream>

using std::istream;
using std::ostream;
using std::cin;
using std::cout;

const int INF = 0x3f3f3f3f;

class Point {
    friend istream &operator >>(istream &is, Point &p) {
        is >> p.x >> p.y >> p.z;
        return is;
    }

public:
    double x, y, z;

    bool operator ==(const Point &other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    bool operator !=(const Point &other) const {
        return !(*this == other);
    }
};

bool checkCoef(const double &coef, const Point &a, const Point &b, const Point &c) {
    return c.x - a.x == coef * (b.x - a.x) &&
            c.y - a.y == coef * (b.y - a.y) &&
            c.z - a.z == coef * (b.z - a.z);
}

double getCoef(const Point &a, const Point &b, const Point &c) {
    if (a == b) {
        return INF;
    }

    // vec(A1 A3) = a * vec(A1 A2)
    double coef;
    if (a.x != b.x) {
        coef = (c.x - a.x) / (b.x - a.x);
    }
    else if (a.y != b.y) {
        coef = (c.y - a.y) / (b.y - a.y);
    }
    else {
        coef = (c.z - a.z) / (b.z - a.z);
    }

    if (checkCoef(coef, a, b, c)) {
        return coef;
    }

    return -INF;
}

void printEquation(const double &coef) {
    if (coef == INF) {
        cout << "A1 = 1 * A2 + 0 * A3\n";
    }
    else {
        cout << "A3 = " << 1 - coef << " * A1 + " << coef << " * A2\n";
    }
}

int main() {
    Point a, b, c;
    cin >> a >> b >> c;
    double coef = getCoef(a, b, c);

    cout << "a) ";
    if (coef != -INF) {
        cout << "DA\nb) ";
        printEquation(coef);
    }
    else {
        cout << "NU\n";
    }

    return 0;
}