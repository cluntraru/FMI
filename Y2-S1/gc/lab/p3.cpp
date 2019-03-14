#include <iostream>
#include <cmath>

const double kEps = 1e-6;

using std::cin;
using std::cout;
using std::swap;

class Point {
public:
    double x, y;

    bool operator <(const Point &other) const {
        if (x - other.x < kEps && x - other.x > -kEps) {
            return (y - other.y) < -kEps;
        }

        return (x - other.x) < -kEps;
    }

    bool operator ==(const Point &other) const {
        double diff1 = x - other.x;
        double diff2 = y - other.y;
        return diff1 < kEps && diff1 > -kEps && diff2 < kEps && diff2 > -kEps;
    }
};

class Segment {
public:
    Point a, b;
};

class Matrix22 {
public:
    double content[4];

    Matrix22(double a11, double a12, double a21, double a22) {
        content[0] = a11;
        content[1] = a12;
        content[2] = a21;
        content[3] = a22;
    }

    double det() {
        return content[0] * content[3] - content[1] * content[2];
    }
};

void Read(Segment &s) {
    cin >> s.a.x >> s.a.y >> s.b.x >> s.b.y;
}

void Order(Segment &s) {
    if (s.b.x < s.a.x) {
        swap(s.a, s.b);
    }
    else if (s.b.x == s.a.x && s.b.y < s.a.y) {
        swap(s.a, s.b);
    }
}

double Dist(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool OnSegmentIfOnLine(Segment s, Point p) {
    double diff1 = Dist(p, s.a) + Dist(p, s.b) - Dist(s.a, s.b);
    return diff1 < kEps && diff1 > -kEps;
}

bool IsZero(double x) {
    return x > -kEps && x < kEps;
}

int main() {
    Segment s1, s2;
    Read(s1);
    Read(s2);

    Order(s1);
    Order(s2);

    // s1: | x      y      1 |
    //     | s1.a.x s1.a.y 1 |
    //     | s1.b.x s1.b.y 1 |
    double a1 = s1.a.y - s1.b.y;
    double b1 = s1.b.x - s1.a.x;
    double c1 = s1.a.x * s1.b.y - s1.a.y * s1.b.x;

    double a2 = s2.a.y - s2.b.y;
    double b2 = s2.b.x - s2.a.x;
    double c2 = s2.a.x * s2.b.y - s2.a.y * s2.b.x;

    Matrix22 A = Matrix22(a1, b1, a2, b2);

    if (!IsZero(A.det())) {
        Point p = Point();
        p.x = Matrix22(-c1, b1, -c2, b2).det() / A.det();
        p.y = Matrix22(a1, -c1, a2, -c2).det() / A.det();

        // double ec1 = a1 * p.x + b1 * p.y + c1;
        // double ec2 = a2 * p.x + b2 * p.y + c2;
        //
        // cout << a1 << ' ' << b1 << ' ' << c1 << '\n';
        // cout << a2 << ' ' << b2 << ' ' << c2 << '\n';
        // cout << ec1 << ' ' << ec2 << '\n';
        if (OnSegmentIfOnLine(s1, p) && OnSegmentIfOnLine(s2, p)) {
            cout << "Intersectia este: (" << p.x << ", " << p.y << ")\n";
        }
        else {
            cout << "Segmentele nu se intersecteaza\n";
        }
    }
    else {
        Matrix22 A_ext_m1 = Matrix22(a1, c1, a2, c2);
        Matrix22 A_ext_m2 = Matrix22(b1, c1, b2, c2);

        if (!IsZero(A_ext_m1.det()) || !IsZero(A_ext_m2.det())) {
            // rang(A_ext) = 2
            cout << "Segmentele nu se intersecteaza\n";
        }
        else {
            // rang(A_ext) = 1, deci coliniare
            if (s2.a < s1.b) {
                cout << "Intersectia este: [(" << s2.a.x << ", " << s2.a.y << "), (" <<
                        s1.b.x << ", " << s1.b.y << ")]\n";
            }
            else if (s2.a == s1.b) {
                cout << "Intersectia este: (" << s2.a.x << ", " << s2.a.y << ")\n";
            }
            else {
                cout << "Segmentele nu se intersecteaza\n";
            }
        }
    }
    return 0;
}
