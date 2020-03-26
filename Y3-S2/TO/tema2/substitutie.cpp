#include <iostream>
#include <fstream>

std::ifstream fin("subs.in");

const int MaxN = 1005;

double y[MaxN];
double v[MaxN];
double v1[MaxN];
double b[MaxN][MaxN];
double b1[MaxN][MaxN];

int main() {
    int n;
    fin >> n;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fin >> b[i][j];
        }
    }

    for (int i = 0; i < n; ++i) {
        fin >> y[i];
    }

    for (int i = 0; i < n; ++i) {
        fin >> v[i];
    }


    int subsIdx = -1; // i din enunt
    for (int i = 0; i < n; ++i) {
        if (y[i] != 0) {
            subsIdx = i;
            break;
        }
    }

    std::cout << '\n';

    if (subsIdx == -1) {
        std::cout << "y este nul, nu putem continua\n";
        return 0;
    }

    // Cream B1
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (subsIdx == i) {
                b1[i][j] = y[j];
            } else {
                b1[i][j] = b[i][j];
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (subsIdx == i) {
            v1[i] = v[subsIdx] / y[subsIdx];
        } else {
            v1[i] = v[i] - v[subsIdx] / y[subsIdx] * y[i];
        }
    }

    std::cout << "Baza noua (B1): \n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << b1[i][j] << ' ';
        }

        std::cout << '\n';
    }

    std::cout << "\nVector transformat (v'): ";
    for (int i = 0; i < n; ++i) {
        std::cout << v1[i] << ' ';
    }

    return 0;
}
