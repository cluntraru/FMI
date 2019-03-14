/* Fie Ai(xi, yi) in R^2, i de la 1 la 4 distincte 2 cate 2.
    Sa se determine multimile I, J a.i. I \cup J = {A1, A2, A3, A4} si I \cap J = \Phi si
    conv(I) \cap conv(J) != \Phi
*/

#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::sort;
using std::for_each;

struct Point {
    double x, y;
    int idx;
};

inline double CrossProduct(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

vector  <Point> ConvexHull(vector <Point> points) {
    int best_idx = 0;
    for (int i = 1; i < points.size(); ++i) {
        if (points[i].x < points[best_idx].x) {
            best_idx = i;
        }
        else if (points[i].x == points[best_idx].x && points[i].y < points[best_idx].y) {
            best_idx = i;
        } 
    }

    std::swap(points[0], points[best_idx]);

    sort(points.begin() + 1, points.end(), [&points](const Point &a, const Point &b) {
        return CrossProduct(points[0], a, b) < 0;
    });

    vector<Point> stk;
    for_each(points.begin(), points.end(), [&stk](const Point &p) {
        if (stk.size() >= 2) {
            Point last_val_1 = stk[stk.size() - 2];
            Point last_val_2 = stk[stk.size() - 1];
            while (stk.size() >= 2 and CrossProduct(last_val_1, last_val_2, p) >= 0) {
                stk.pop_back();
                last_val_1 = stk[stk.size() - 2];
                last_val_2 = stk[stk.size() - 1];
            }
        }

        stk.push_back(p);
    });

    return stk;
}

inline void PrintIJ(const vector<Point> &points, const vector<Point> &hull) {
    // cout << "Hull = ";
    // for_each(hull.begin(), hull.end(), [] (const Point &p) {
    //     cout << p.idx << ' ';
    // });
    // cout << '\n';

    if (hull.size() == 4) {
        cout << "I = " << hull[0].idx + 1 << ' ' << hull[2].idx + 1 << '\n';
        cout << "J = " << hull[1].idx + 1 << ' ' << hull[3].idx + 1 << '\n';
        return;
    }

    bool used[4];
    for (int i = 0; i < 4; ++i) {
        used[i] = false;
    }

    cout << "I = ";
    for (int i = 0; i < hull.size(); ++i) {
        cout << hull[i].idx + 1 << ' ';
        used[hull[i].idx] = true;
    }
    cout << '\n';

    cout << "J = ";
    for (int i = 0 ; i < 4; ++i) {
        if (!used[points[i].idx]) {
            cout << points[i].idx + 1 << ' ';
        }
    }
    cout << '\n';
}

int main() {
    vector<Point> points;

    for (int i = 0; i < 4; ++i) {
        Point a;
        cin >> a.x >> a.y;
        a.idx = i;

        points.push_back(a);
    }

    auto hull = ConvexHull(points);

    PrintIJ(points, hull);

    return 0;
}