/*
 * Se introduce matricea pentru problema de maximizare sub forma
 * numarLinii, numarColoane
 * matrice
 *
 * Exemplu:
 * 3x + 5y <= 78
 * 4x + y <= 36
 * x, y >= 0
 * P = 5x + 4y
 *
 * Output:
 * Variabila 1 este valoarea lui x
 * Var 2 ... y
 * Var 3 ... u
 * Var 4 ... w
 * var 5 ... P
 */

#include <fstream>
#include <iostream>

std::ifstream fin("simplex.in");

const int g_MaxN = 1005;
const double g_Eps = 1e-3;

double mat[g_MaxN][g_MaxN];

void AddLines(int m, double *l1, double *l2, double coef) {
    for (int colIdx = 0; colIdx < m; ++colIdx) {
        l2[colIdx] += coef * l1[colIdx];
    }
}

void DivLine(int m, double *lin, double coef) {
    for (int colIdx = 0; colIdx < m; ++colIdx) {
        lin[colIdx] /= coef;
    }
}

bool eq(const double &a, const double &b) {
    return a - b < g_Eps && a - b > -g_Eps;
}

int main() {
    int n, m; // Numar linii, numar coloane
    fin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            fin >> mat[i][j];
        }
    }

    bool foundNegative = true;
    while (foundNegative) {
        // Parcurgem numerele de pe linia problemei de optimizare (ultima)
        // pentru a gasi cel mai mic numar negativ
        int pivotColIdx = 0;
        foundNegative = false;
        for (int colIdx = 0; colIdx < m - 1; ++colIdx) {
            double currVal = mat[n - 1][colIdx];
            double oldMinVal = mat[n - 1][pivotColIdx];

            if (currVal < 0 && (!foundNegative || currVal < oldMinVal)) {
                foundNegative = true;
                pivotColIdx = colIdx;
            }
        }

        // Daca nu am gasit niciun numar negativ, am terminat
        if (!foundNegative) {
            break;
        }

        // Daca am gasit un numar negativ, cautam linia pivotului
        double minPostDiv = (1 << 30);
        int pivotLinIdx = 0;
        for (int linIdx = 0; linIdx < n - 1; ++linIdx) {
            if (eq(mat[linIdx][pivotColIdx], 0)) {
                continue;
            }

            double potentialDivCoef = mat[linIdx][m - 1] / mat[linIdx][pivotColIdx];
            if (potentialDivCoef < minPostDiv) {
                minPostDiv = potentialDivCoef;
                pivotLinIdx = linIdx;
            }
        }

        // Impartim linia pivotului la pivot pt a obtine 1
        DivLine(m, mat[pivotLinIdx], mat[pivotLinIdx][pivotColIdx]);

        // Am gasit pivotul, acum scadem din celelalte linii
        for (int linIdx = 0; linIdx < n; ++linIdx) {
            if (linIdx == pivotLinIdx) {
                continue;
            }

            double coef = -mat[linIdx][pivotColIdx];
            AddLines(m, mat[pivotLinIdx], mat[linIdx], coef);
        }

//        for (int i = 0; i < n; ++i) {
//            for (int j = 0; j < m; ++j) {
//                std::cout << mat[i][j] << ' ';
//            }
//
//            std::cout << '\n';
//        }
//
//        std::cout << "\n\n";
    }

    // Odata ce am terminat de prelucrat matricea, extragem rezultatele
    for (int colIdx = 0; colIdx < m - 1; ++colIdx) {
        int oneIdx = -1;
        bool isValid = true;
        for (int linIdx = 0; linIdx < n; ++linIdx) {
            int currVal = mat[linIdx][colIdx];
            if (oneIdx == -1 && currVal == 1) {
                oneIdx = linIdx;
            } else if (oneIdx != -1 && currVal == 1) {
                isValid = false;
            } else if (currVal != 0 && currVal != 1) {
                isValid = false;
            }
        }
    
        std::cout << "Variabila " << colIdx + 1 << " = ";
        if (oneIdx != -1 && isValid) {
            std::cout << mat[oneIdx][m - 1] << '\n';
        } else {
            std::cout << "0\n";
        }
    }
    return 0;
}
