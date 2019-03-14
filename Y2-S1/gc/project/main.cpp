#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <vector>

using std::cin;
using std::cout;
using std::istream;
using std::ostream;
using std::vector;
using std::sort;
using std::swap;

std::ifstream fin("test.in");

const double kEps = 1e-6;

// Less than
inline bool lt(double a, double b) {
    return a - b < -kEps;
}

// Equal
inline bool eq(double a, double b) {
    return a - b < kEps && a - b > -kEps;
}

// Square
inline double sq(double x) {
    return x * x;
}

class Point {
    friend const istream &operator >>(istream &is, Point &p) {
        is >> p.x >> p.y;
        return is;
    }

public:
    double x, y;

    double dist(const Point &other) const {
        return sqrt(sq(x - other.x) + sq(y - other.y));
    }

    bool operator <(const Point &other) const {
        if (eq(x, other.x)) {
            return lt(y, other.y);
        }
        return lt(x, other.x);
    }
};

inline double cross_product(const Point &a, const Point &b, const Point &c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

class Triangle {
public:
    Point a, b, c;

    Triangle(const Point &a, const Point &b, const Point &c) {
        this->a = a;
        this->b = b;
        this->c = c;
    }

    bool in_triangle(const Point &p) const {
        return (cross_product(a, b, p) <= 0 && cross_product(b, c, p) <= 0 && cross_product(c, a, p) <= 0) ||
               (cross_product(a, b, p) >= 0 && cross_product(b, c, p) >= 0 && cross_product(c, a, p) >= 0);
    }
};

class Edge {
public:
    Point a, b;

    Edge(const Point &a, const Point &b) {
        this->a = a;
        this->b = b;
    }

    bool on_edge(const Point &p) const {
        return eq(p.dist(a) + p.dist(b), a.dist(b));
    }
};

bool check_edges(const vector<Point> &polygon, const Point &p) {
    for (int i = 1; i < polygon.size(); ++i) {
        Edge edg(polygon[i - 1], polygon[i]);
        if (edg.on_edge(p)) {
            // cout << polygon[i - 1].x << ' ' << polygon[i - 1].y << '\n' << polygon[i].x << ' ' << polygon[i].y << "\n\n\n";
            return true;
        }
    }

    Edge last_edg(polygon[0], polygon.back());
    return last_edg.on_edge(p);
}

bool check_inside(const vector<Point> &polygon, const Point &p) {
    for (int i = 2; i < polygon.size(); ++i) {
        Triangle tr(polygon[0], polygon[i - 1], polygon[i]);
        if (tr.in_triangle(p)) {
            cout << polygon[0].x << ' ' << polygon[0].y << '\n' <<
                    polygon[i - 1].x << ' ' << polygon[i - 1].y << '\n' <<
                    polygon[i].x << ' ' << polygon[i].y << "\n\n\n";
            return true;
        }
    }

    return false;
}

int main() {
    // cout << "Point: ";
    Point query_pnt;
    fin >> query_pnt;

    // cout << "\nNumber of vertices: ";
    int n; // Number of vertices
    fin >> n;

    vector<Point> polygon;
    int min_idx = 0;
    for (int i = 0; i < n; ++i) {
        // cout << "\n Vertex: ";
        Point p;
        fin >> p;
        polygon.push_back(p);

        if (polygon[i] < polygon[min_idx]) {
            min_idx = i;
        }
    }

    swap(polygon[0], polygon[min_idx]);
    sort(polygon.begin() + 1, polygon.end(), [&polygon](const Point &a, const Point &b) {
        return cross_product(polygon[0], a, b) < 0;
    });

    if (check_edges(polygon, query_pnt)) {
        cout << "The point is on the polygon.\n";
    }
    else if (check_inside(polygon, query_pnt)) {
        cout << "The point is inside the polygon.\n";
    }
    else {
        cout << "The point is outside the polygon.\n";
    }

    return 0;
}