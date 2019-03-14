#include <iostream>
#include <fstream>
#include <ctime>

std::ofstream fout ("test.out");

int main() {
    srand(time(NULL));
    int n, m;
    std::cin >> n >> m;
    fout << n << ' ' << m << '\n';
    for (int i = 0; i < m; ++i) {
        int a = rand() % n;
        int b = rand() % n;
        while (b == a) {
            b = rand() % n;
        }

        int c = rand() % (int) 1e5;


        fout << a << ' ' << b << ' ' << c << '\n';
    }
    return 0;
}