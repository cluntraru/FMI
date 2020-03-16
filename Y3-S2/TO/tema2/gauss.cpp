#include <fstream>
#include <iostream>

using namespace std;

ifstream fin ("gauss.in");

const int MaxN = 305;
const double Eps = 1e-3;

int n;
double mat[MaxN][MaxN];
double invMat[MaxN][MaxN];

inline void LineSwap(double v1[MaxN], double v2[MaxN]) {
  for (int i = 1; i <= n; ++i) {
    swap(v1[i], v2[i]);
  }
}

inline void AddLine(double v1[MaxN], double v2[MaxN], double coef) {
  for (int i = 1; i <= n; ++i) {
    v2[i] += v1[i] * coef;
  }
}

int main() {
  fin >> n;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      fin >> mat[i][j];
    }
  }

  for (int i = 1; i <= n; ++i) {
    invMat[i][i] = 1;
  }

  int CurrLin = 1;
  for (int CurrCol = 1; CurrCol <= n; ++CurrCol) {
    if (CurrLin > n) {
      break;
    }

    if (!mat[CurrLin][CurrCol]) {
      for (int i = CurrLin + 1; i <= n; ++i) {
        if (mat[i][CurrCol]) {
          LineSwap(mat[i], mat[CurrLin]);
          LineSwap(invMat[i], invMat[CurrLin]);
          break;
        }
      }

      if (!mat[CurrLin][CurrCol]) { ///CurrLin does not advance, column is "removed"
        continue;
      }
    }

    for (int i = 1; i <= n; ++i) { ///Get all other lines on column to 0
      if (i == CurrLin) {
        continue;
      }

      double coef = -(mat[i][CurrCol] / mat[CurrLin][CurrCol]);
      AddLine(mat[CurrLin], mat[i], coef);
      AddLine(invMat[CurrLin], invMat[i], coef);
    }

    ++CurrLin;
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
        if (mat[i][j] > Eps || mat[i][j] < -Eps) {
            for (int k = 1; k <= n; ++k) {
                invMat[i][k] /= mat[i][j];
            }
        }
    }
  }

  for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        cout << invMat[i][j] << ' ';
      }
      cout << '\n';
  }
  cout << '\n';

//  for (int i = 1; i <= n; ++i) {
//    for (int j = 1; j <= n; ++j) {
//      cout << mat[i][j] << ' ';
//    }
//
//    cout << '\n';
//  }

  return 0;
}
