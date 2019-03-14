#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using std::vector;

std::ifstream fin("stergeri.in");
std::ofstream fout("stergeri.out");

int n, m, k;

class Intv {
public:
    int lf, rg;

    Intv(int lf, int rg) {
        this->lf = lf;
        this->rg = rg;
    }
};

vector<Intv> v;

int main() {
    fin >> n >> m >> k;
    for (int i = 0; i < m; ++i) {
        int x, y;
        fin >> x >> y;
        v.push_back(Intv(x, y));
    }

    std::reverse(v.begin(), v.end());
    for (int i = 0; i < m; ++i) {
        if (v[i].lf <= k) {
            k += v[i].rg - v[i].lf + 1;
        }
    }

    fout << k << '\n';
    return 0;
}