#include <fstream>

using std::pair;
using std::make_pair;

std::ifstream fin("minmaxstore.in");
std::ofstream fout("minmaxstore.out");

const int N_MAX = 100005;

bool minPossible[N_MAX], maxPossible[N_MAX];

void clear(int n) {
    for (int i = 0; i <= n; ++i) {
        maxPossible[i] = minPossible[i] = true;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    fin.tie(0);
    int T;
    fin >> T;
    for (int test = 0; test < T; ++test) {
        int n, m, pMin, pMax;
        fin >> n >> m;
        clear(n);

        int minCnt = n;
        int maxCnt = n;
        for (int i = 0; i < m; ++i) {
            int x, y;
            fin >> x >> y;

            if (minPossible[y] && !minPossible[x]) {
                minPossible[x] = true;
                ++minCnt;
            }

            if (minPossible[y]) {
                minPossible[y] = false;
                --minCnt;
            }

            if (maxPossible[x] && !maxPossible[y]) {
                maxPossible[y] = true;
                ++maxCnt;
            }

            if (maxPossible[x]) {
                maxPossible[x] = false;
                --maxCnt;
            }
        }

        fin >> pMin >> pMax;

        bool minOk = (minCnt == 1 && minPossible[pMin]);
        bool maxOk = (maxCnt == 1 && maxPossible[pMax]);

        if (minOk && maxOk) {
            fout << "Popeala\n";
        }
        else if (minOk) {
            fout << "Popel\n";
        }
        else if (maxOk) {
            fout << "Popita\n";
        }
        else {
            fout << "Comisarul\n";
        }
    }
    return 0;
}