#include <fstream>

std::ifstream fin("hacker3.in");
std::ofstream fout("hacker3.out");

/*

dp[i][j] = costul pana la pozitia i cu j de a alese

*/

using std::min;
using std::max;

const int kMaxN = 100005;
const int kMaxA = 32;

int a[kMaxN], b[kMaxN];
long long dp[2][kMaxA + 5];

int main() {
    int n;
    fin >> n;
    for (int i = 0; i < n; ++i) {
        fin >> a[i] >> b[i];
    }


    // for (int i = 0; i <= kMaxA; ++i) {
    //     dp[0][i] = -1;
    // }

    dp[0][0] = b[0];
    dp[0][1] = a[0];

    int lin = 1;
    for (int i = 1; i < n; ++i, lin = !lin) {
        dp[lin][0] = dp[!lin][0] + b[i];

        for (int a_cnt = 1; a_cnt <= kMaxA && a_cnt <= i + 1; ++a_cnt) {
            long long multiplier = (1LL << (a_cnt - 1));

            if (a_cnt == i + 1) {
                dp[lin][a_cnt] = dp[!lin][a_cnt - 1] + multiplier * a[i];
            }
            else {
                dp[lin][a_cnt] = min(dp[!lin][a_cnt - 1] + multiplier * a[i], dp[!lin][a_cnt] + (multiplier << 1) * b[i]);
            }
        }
    }

    long long ans = (1LL << 60);
    for (int i = 0; i <= n && i <= kMaxA; ++i) {
        if (dp[!lin][i] == -1) {
            continue;
        }

        ans = min(ans, dp[!lin][i]);
    }

    fout << ans << '\n';
    return 0;
}