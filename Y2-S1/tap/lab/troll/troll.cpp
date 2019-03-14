#include <fstream>
#include <vector>
#include <algorithm>

std::ifstream fin("troll.in");
std::ofstream fout("troll.out");

using std::max;
using std::vector;
using std::min;

const int N_MAX = 100005;
const int INF = 2147483647;

struct Interval {
    int x, y, val, idx;
};

Interval v[N_MAX];
vector<Interval> added;
int rgOf[N_MAX], lfOf[N_MAX];
int n;

int lowerBound(int lf, int rg, int x) {
    int ans = -1;
    while (lf <= rg) {
        int med = (lf + rg) / 2;
        if (added[med].y < x) {
            ans = med;
            lf = med + 1;
        }
        else {
            rg = med - 1;
        }
    }

    return ans + 1;
}

int upperBound(int lf, int rg, int y) {
    int ans = -1;
    while (lf <= rg) {
        int med = (lf + rg) / 2;
        if (added[med].x > y) {
            ans = med;
            lf = med + 1;
        }
        else {
            rg = med - 1;
        }
    }

    return ans + 1;
}

void lfActivitySelection() {
    for (int i = 0; i < n; ++i) {
        int lastY = (!added.empty()) ? added.back().y : -INF;

        if (v[i].val == 0) { // Found a special one
            int idx = v[i].idx;
            lfOf[idx] = lowerBound(0, added.size() - 1, v[i].x);
        }

        if (v[i].x > lastY) {
            added.emplace_back(v[i]);
        }
    }
}

void rgActivitySelection() {
    added.clear();
    for (int i = n - 1; i >= 0; --i) {
        int lastX = (!added.empty()) ? added.back().x : INF;
        if (v[i].val == 0) { // Found a special one
            int idx = v[i].idx;
            rgOf[idx] = upperBound(0, added.size() - 1, v[i].y);
        }

        if (v[i].y < lastX) {
            added.emplace_back(v[i]);
        }
    }
}

int countIntervals() {
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (v[i].val == 1) {
            continue;
        }

        int idx = v[i].idx;
        ans = max(ans, lfOf[idx] + rgOf[idx] + 1);
    }

    return ans;
}

int main() {
    fin >> n;

    int maxVal = -1338;
    for (int i = 0; i < n; ++i) {
        fin >> v[i].x >> v[i].y >> v[i].val;
        v[i].idx = i;
        maxVal = max(maxVal, v[i].val);
    }

    for (int i = 0; i < n; ++i) {
        if (v[i].val < maxVal) {
            v[i].val = 1;
        }
        else {
            v[i].val = 0;
        }
    }

    std::sort(&v[0], &v[n], [](const Interval &a, const Interval &b) {
        if (a.y == b.y) {
            return a.x < b.x;
        }

        return a.y < b.y;
    });

    lfActivitySelection();

    std::sort(&v[0], &v[n], [](const Interval &a, const Interval &b) {
        if (a.x == b.x) {
            return a.y < b.y;
        }

        return a.x < b.x;
    });

    rgActivitySelection();

    fout << maxVal << ' ' << countIntervals() << '\n';
    return 0;
}