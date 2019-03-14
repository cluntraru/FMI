#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <cstring>

std::ifstream fin("test.in");
std::ofstream fout("test.out");

const int MaxS = 100005;

int S, L, Entry, EndCnt, EdgCnt, WordCnt;

std::vector <int> states;
std::vector <char> letters;
std::vector <int> LambdaEq[MaxS];

bool isEnd[MaxS];
class AutomatonEdge {
public:
    int state;
    char letter;

    AutomatonEdge() : state(1), letter(2) {}

    AutomatonEdge(int _state, char _letter) : state(_state), letter(_letter) {}

    bool operator < (const AutomatonEdge &other) const {
        return state < other.state;
    }
};

//std::map <AutomatonEdge, bool> used;

std::vector <AutomatonEdge>  Automaton[MaxS];

bool IsValid(int state, const std::string &str, int pos = 0) {
    if (pos == str.size()) {
        for (int currLambda: LambdaEq[state]) {
            if (isEnd[currLambda]) {
                return true;
            }
        }

        return false;
    }

    std::vector <int> nxtStates;
    for (int currLambda: LambdaEq[state]) { //we iterate through all the states we can freely get to from current state
        for (AutomatonEdge edg: Automaton[currLambda]) { //for each of these available state, we try to pass through the given letter
            if (edg.letter != str[pos]) { //we are not interested in edges that don't correspond to the one we want
                continue;
            }

            int nxtState = edg.state;
            for (int lambdaNxt: LambdaEq[nxtState]) { //now that we got to a new state, we actually got to all the lambda-equal states to it
                nxtStates.emplace_back(lambdaNxt);
            }
        }
    }

    for (int nxtState: nxtStates) {
        if (IsValid(nxtState, str, pos + 1)) {
            return true;
        }
    }

    return false;
}

bool lambdaUsed[MaxS];

void LambdaDfs(int node, int rt) {
    lambdaUsed[node] = true;
    LambdaEq[rt].emplace_back(node);

    for (int edg: LambdaEq[node]) {
        if (lambdaUsed[edg]) {
            continue;
        }

        LambdaDfs(edg, rt);
    }
}

void GenerateLambdaEq() {
    for (int node: states) {
        memset(lambdaUsed, false, sizeof(lambdaUsed));
        LambdaDfs(node, node);
    }
}

int main() {
    fin >> S;
    for (int i = 0; i < S; ++i) {
        int x;
        fin >> x;
        states.emplace_back(x);
    }

    fin >> L;
    for (int i = 0; i < L; ++i) {
        char x;
        fin >> x;
        letters.emplace_back(x);
    }

    fin >> Entry;

    fin >> EndCnt;
    for (int i = 0; i < EndCnt; ++i) {
        int x;
        fin >> x;
        isEnd[x] = true;
    }

    fin >> EdgCnt;
    for (int i = 0; i < EdgCnt; ++i) {
        int a, b;
        char ch;

        fin >> a >> ch >> b;

        if (ch == '.') {
            LambdaEq[a].emplace_back(b);
        }
        else {
            Automaton[a].emplace_back(AutomatonEdge(b, ch));
        }
    }

//    for (int state: states) {
//        LambdaEq[state].emplace_back(state);
//    }

    GenerateLambdaEq();
    fin >> WordCnt;
    for (int i = 0; i < WordCnt; ++i) {
        std::string str;
        fin >> str;
//        fout << str << ' ';
        if (IsValid(Entry, str)) {
            fout << "DA\n";
        }
        else {
            fout << "NU\n";
        }
    }
    return 0;
}