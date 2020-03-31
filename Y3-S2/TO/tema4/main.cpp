/*
 * Se introduce matricea pentru problema de minimizare sub forma
 * numarLinii, numarColoane
 * matrice
 *
 * Exemplu:
 * 2x + y + 3z >= 6
 * x + 2y + 4z >= 8
 * 3x + y - 2z >= 4
 * C = x + y + 3z
 *
 * Output:
 * Variabila 1 este valoarea lui x
 * Var 2 ... y
 * Var 3 ... z
 * Var 4 ... C
 *
 */

#include <fstream>
#include <iostream>

std::ifstream fin("simplex.in");

const int g_MaxN = 1005;
const double g_Eps = 1e-3;

double miniMat[g_MaxN][g_MaxN];
double mat[g_MaxN][g_MaxN];

int oldN, oldM;

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

void CreateMat(int &n, int &m) {
    // Transpunem matricea
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            mat[i][j] = miniMat[j][i];
        }
    }

    int newM = m + n;

    // Mutam ultima coloana pe pozitia noua de la ultima coloana 
    for (int i = 0; i < n - 1; ++i) {
        mat[i][newM - 1] = mat[i][m - 1];
        mat[i][m - 1] = 0;
    }

    // Negam numerele de pe ultima linie (problema de minimizare devine una de maximizare)
    for (int j = 0; j < m - 1; ++j) {
        mat[n - 1][j] = -mat[n - 1][j];
    }

    oldN = n;
    oldM = m;

    m = newM;

    // Punem 1 pe diagonala la variabilele suplimentare
    for (int i = 0; i < n; ++i) {
        mat[i][i + oldM - 1] = 1;
    }
}

int main() {
    int n, m; // Numar linii, numar coloane
    fin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            fin >> miniMat[i][j];
        }
    }

    CreateMat(n, m);

    std::cout << "Matricea de maximizare = \n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cout << mat[i][j] << ' ';
        }

        std::cout << '\n';
    }

    std::cout << "\n\n";

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
    }

    // Odata ce am terminat de prelucrat matricea, extragem rezultatele
    int varIdx = 1;
    for (int colIdx = oldM - 1; colIdx < m; ++colIdx) {
        if (colIdx == m - 2) {
            continue;
        }

        std::cout << "Variabila " << varIdx << " = ";
        varIdx++;
        std::cout << mat[n - 1][colIdx] << '\n';
    }
    return 0;
}
