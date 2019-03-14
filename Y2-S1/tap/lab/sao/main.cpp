#include <iostream>
#include <fstream>
#include <queue>

std::ifstream fin("sao.in");
std::ofstream fout("sao.out");

int n, k;
long long hp;

class PQNode {
public:
    int dmg;

    PQNode(int dmg) {
        this->dmg = dmg;
    }

    bool operator <(const PQNode &other) const {
        return dmg < other.dmg;
    }
};

std::priority_queue<PQNode> pq;

int main() {
    fin >> n >> k >> hp;
    int mon_cnt;
    for (mon_cnt = 0; mon_cnt < n && hp > 0; ++mon_cnt) {
        int curr_dmg;
        fin >> curr_dmg;
        pq.push(PQNode(curr_dmg));

        while (!pq.empty() && hp - curr_dmg <= 0 && k > 0 && pq.top().dmg > 0) {
            hp += pq.top().dmg;
            pq.pop();
            --k;
        }

        hp -= curr_dmg;
    }

    if (hp < 0) {
        --mon_cnt;
    }
    
    fout << mon_cnt << '\n';
    return 0;
}