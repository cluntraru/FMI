/***
 * Lambda = '~'
 * Input format:
 * InputWord
 * NumberOfStates NumberOfEdges IndexOfInitialState NumberOfEndStates
 * EndState0 Endstate1 EndState2 ... EndState(NumberOfEndStates - 1)
 * EdgeStartState0 EdgeEndState0 EdgeTransitionSymbol0 EdgeOutSymbol0
 * EdgeStartState1 EdgeEndState1 EdgeTransitionSymbol1 EdgeOutSymbol1
 * ...
 * EdgeStartState(NumberOfEndStates - 1) EdgeEndState(Num - 1) EdgeTransitionSymbol(Num - 1) EdgeOutSymbol(Num - 1)
 */

#include <fstream>
#include <map>
#include <vector>

const char g_Lambda = '~'; // Tilda este lambda
// Numarul maxim de outputuri (limitat in caz ca exista o bucla cu intrare lambda pe o stare finala)
const int g_OutputCap = 1e3;

std::ifstream fin("tc1.in");
std::ofstream fout("tc1.out");

class Edge;

struct State {
    std::vector<Edge *> edges;
    bool isEndState;
};

struct Edge {
    State *stState;
    State *edState;
    char transitionSymb, outSymb;
};

std::vector<char> g_PrintStk;
std::vector<State*> g_States;
std::vector<Edge *> g_Edges;

int g_FlushCnt = 0;
int g_StateCnt, g_EdgeCnt, g_StartState, g_EndStateCnt;
std::string g_InWord;

void FlushStack() {
    fout << "Output " << g_FlushCnt << ": ";
    for (char ch: g_PrintStk) {
        if (ch != g_Lambda) {
            fout << ch << ' ';
        }
    }

    fout << '\n';
    ++g_FlushCnt;
}

void Dfs(State *currState, int inWordIdx) {
    if (g_FlushCnt == g_OutputCap) {
        return;
    }

    if (inWordIdx == g_InWord.size()) {
        if (currState->isEndState) {
            FlushStack();
        }
    }

    for (Edge *edge: currState->edges) {
        // If word is over, only lambdas need checking
        if (inWordIdx < g_InWord.size() && edge->transitionSymb == g_InWord[inWordIdx]) {
            g_PrintStk.push_back(edge->outSymb);
            Dfs(edge->edState, inWordIdx + 1);
            g_PrintStk.pop_back();
        } else if (edge->transitionSymb == g_Lambda) {
            g_PrintStk.push_back(edge->outSymb);
            Dfs(edge->edState, inWordIdx);
            g_PrintStk.pop_back();
        }
    }
}

int main() {
    fin >> g_InWord;
    fin >> g_StateCnt >> g_EdgeCnt >> g_StartState >> g_EndStateCnt;
    for (int i = 0; i < g_StateCnt; ++i) {
        State *state = new State();
        g_States.push_back(state);
    }

    for (int i = 0; i < g_EndStateCnt; ++i) {
        int stateIdx;
        fin >> stateIdx;
        g_States[stateIdx]->isEndState = true;
    }

    for (int i = 0; i < g_EdgeCnt; ++i) {
        int stStateIdx, edStateIdx;
        Edge *edge = new Edge();
        fin >> stStateIdx >> edStateIdx;
        fin >> edge->transitionSymb >> edge->outSymb;
        edge->stState = g_States[stStateIdx];
        edge->edState = g_States[edStateIdx];
        edge->stState->edges.push_back(edge);

        g_Edges.push_back(edge);
    }

    Dfs(g_States[g_StartState], 0);

    for (int i = 0; i < g_StateCnt; ++i) {
        delete g_States[i];
    }

    for (int i = 0; i < g_EdgeCnt; ++i) {
        delete g_Edges[i];
    }
    return 0;
}
