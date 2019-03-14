#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using std::for_each;
using std::cout;

std::ifstream fin("permutari.in");
std::ofstream fout("permutari.out");

std::vector<int> stk;
int n;

void print_perm() {
    for_each(stk.begin(), stk.end(), [](const int &x) {
        fout << x << ' ';
    });

    fout << '\n';
}

void bkt(int bitmask = 0) {
    if (stk.size() == n) {
        print_perm();
        return;
    }

    for (int i = 0; i < n; ++i) {
        if (!((1 << i) & bitmask)) {
            stk.push_back(i + 1);
            bkt(bitmask | (1 << i));
            stk.pop_back();
        }
    }
}

int main() {
    fin >> n;
    bkt();
    return 0;
}