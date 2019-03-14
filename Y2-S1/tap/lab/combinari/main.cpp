#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using std::for_each;
using std::cout;

std::ifstream fin("combinari.in");
std::ofstream fout("combinari.out");

std::vector<int> stk;
int n, k;

void print_comb() {
    for_each(stk.begin(), stk.end(), [](const int &x) {
        fout << x << ' ';
    });

    fout << '\n';
}

void bkt(int step = 1) {
    // cout << step << '\n';
    // cout.flush();
    if (step > n) {   
        if (stk.size() == k) {
            print_comb();
        }
        
        return;
    }

    stk.push_back(step);
    bkt(step + 1);
    stk.pop_back();
    bkt(step + 1);
}

int main() {
    fin >> n >> k;
    bkt();
    return 0;
}