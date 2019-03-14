#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>

std::ifstream fin("test.in");
std::ofstream fout("test.out");

const int MaxN = 100005;

inline bool IsLetter(const char &x) {
    return (x >= 'a' and x <= 'z') or x == '#';
}

inline bool Concatenate(const char &ch1, const char &ch2) {
    return (ch1 == ')' and ch2 == '(') or (ch1 == ')' and IsLetter(ch2)) or (IsLetter(ch1) and ch2 == '(') or
           (IsLetter(ch1) and IsLetter(ch2)) or (ch1 == '*' and ch2 == '(') or (ch1 == '*' and IsLetter(ch2));
}

//turns a regular expression into postfix form
//all operations except "|" and "." are already in postfix form
std::string ToPostfix(std::string RE) {
    std::string op_stack;
    std::string postfix_RE;

    std::string RE_with_cat;
    RE_with_cat.push_back(RE.front());
    for (int i = 1; i < RE.size(); ++i) {
        if (Concatenate(RE[i - 1], RE[i])) {
            RE_with_cat.push_back('.');
        }

        RE_with_cat.push_back(RE[i]);
    }

    std::for_each(RE_with_cat.begin(), RE_with_cat.end(), [&op_stack, &postfix_RE](const char &x) {
        if (x == '|') {
            while (op_stack.back() == '|' or op_stack.back() == '.') {
                postfix_RE.push_back(op_stack.back());
                op_stack.pop_back();
            }

            op_stack.push_back(x);
        }
        else if (x == '.') {
            while (op_stack.back() == '.') {
                postfix_RE.push_back(op_stack.back());
                op_stack.pop_back();
            }

            op_stack.push_back(x);
        }
        else if (IsLetter(x) or x == '*' or x == '+') {
            postfix_RE.push_back(x);
        }
        else if (x == '(') {
            op_stack.push_back('(');
        }
        else if (x == ')') {
            while (op_stack.back() != '(') {
                postfix_RE.push_back(op_stack.back());
                op_stack.pop_back();
            }

            op_stack.pop_back();
        }
    });

    while (!op_stack.empty()) {
        postfix_RE.push_back(op_stack.back());
        op_stack.pop_back();
    }

    postfix_RE += "#.";
    return postfix_RE;
}

//NA signifies that node is a letter
enum OPCODE {
    CAT,
    OR,
    STAR,
    NA
};

struct ExpTreeNode {
    OPCODE opcode;
    int father, lfSon, rgSon, index;
    char letter;
};

ExpTreeNode nodeAt[MaxN];
int root_node;

inline bool IsUnary(const OPCODE &opcode) {
    return opcode == STAR;
}

inline OPCODE OpToCode(const char &x) {
    switch (x) {
        case '*':
            return STAR;
        case '|':
            return OR;
        case '.':
            return CAT;
        default:
            return NA;
    }
}

inline void Attach(const int &optor, const int &operand) {
    nodeAt[operand].father = optor;

    nodeAt[optor].lfSon = operand;
}

inline void Attach(const int &optor, const int &operandLf, const int &operandRg) {
    nodeAt[operandLf].father = optor;
    nodeAt[operandRg].father = optor;

    nodeAt[optor].lfSon = operandLf;
    nodeAt[optor].rgSon = operandRg;
}

int letter_nr, symb_nr;

//nodes that are not letters are numbered with larger values than the letters (lettter_cnt...)
void MakeExpressionTree(std::string RE) {
    std::for_each(RE.begin(), RE.end(), [](const char &ch) {
        if (IsLetter(ch)) {
            nodeAt[letter_nr].index = letter_nr;
            nodeAt[letter_nr].lfSon = -1;
            nodeAt[letter_nr].rgSon = -1;
            nodeAt[letter_nr].opcode = NA;
            nodeAt[letter_nr].father = -1;
            nodeAt[letter_nr].letter = ch;
            ++letter_nr;
        }
    });

    symb_nr = letter_nr;
    std::for_each(RE.begin(), RE.end(), [](const char &ch) {
        if (!IsLetter(ch)) {
            nodeAt[symb_nr].index = symb_nr;
            nodeAt[symb_nr].lfSon = -1;
            nodeAt[symb_nr].rgSon = -1;
            nodeAt[symb_nr].opcode = OpToCode(ch);
            nodeAt[symb_nr].father = -1;
            nodeAt[symb_nr].letter = 0;
            ++symb_nr;
        }
    });

    std::vector<int> tree_stack;
    int OP_index = letter_nr;
    int LET_index = 0;
    std::for_each(RE.begin(), RE.end(), [&tree_stack, &OP_index, &LET_index](const char &ch) {
        if (IsLetter(ch)) {
            tree_stack.push_back(LET_index);
            ++LET_index;
        }
        else if (ch == '*') {
            int operand = tree_stack.back();
            tree_stack.pop_back();

            Attach(OP_index, operand);

            tree_stack.push_back(OP_index);
            ++OP_index;
        }
        else if (!IsLetter(ch)) {
            int operandRg = tree_stack.back();
            tree_stack.pop_back();

            int operandLf = tree_stack.back();
            tree_stack.pop_back();

            Attach(OP_index, operandLf, operandRg);

            tree_stack.push_back(OP_index);
            ++OP_index;
        }
    });

    //last concatenation (with '#')
    root_node = (int) RE.size() - 1;
}

//firstPos[node][x] = true if x is in firstpos[node]
std::vector <int> firstPos[MaxN];
std::vector <int> lastPos[MaxN];
bool nullable[MaxN];
std::vector <int> followPos[MaxN];

std::vector <int> Union(std::vector <int> s1, std::vector <int> s2) {
    std::for_each(s2.begin(), s2.end(), [&s1](const int &x) {
        s1.push_back(x);
    });

    sort(s1.begin(), s1.end());
    s1.erase(std::unique(s1.begin(), s1.end()), s1.end());

    return s1;
}

void CalcFirstPos(const ExpTreeNode &node) {
    if (node.lfSon == -1 and node.rgSon == -1) {
        //leaf
        firstPos[node.index] = {node.index};
    }
    else if (node.opcode == OR) {
        firstPos[node.index] = Union(firstPos[node.lfSon], firstPos[node.rgSon]);
    }
    else if (node.opcode == CAT) {
        if (nullable[node.lfSon]) {
            firstPos[node.index] = Union(firstPos[node.lfSon], firstPos[node.rgSon]);
        }
        else {
            firstPos[node.index] = firstPos[node.lfSon];
        }
    }
    else if (node.opcode == STAR) {
        firstPos[node.index] = firstPos[node.lfSon];
    }
}

void CalcLastPos(const ExpTreeNode &node) {
    if (node.lfSon == -1 and node.rgSon == -1) {
        //leaf
        lastPos[node.index] = {node.index};
    }
    else if (node.opcode == OR) {
        lastPos[node.index] = Union(lastPos[node.lfSon], lastPos[node.rgSon]);
    }
    else if (node.opcode == CAT) {
        if (nullable[node.rgSon]) {
            lastPos[node.index] = Union(lastPos[node.lfSon], lastPos[node.rgSon]);
        }
        else {
            lastPos[node.index] = lastPos[node.rgSon];
        }
    }
    else if (node.opcode == STAR) {
        lastPos[node.index] = lastPos[node.lfSon];
    }
}

void CalcNullable(const ExpTreeNode &node) {
    if (node.lfSon == -1 and node.rgSon == -1) {
        //leaf
        nullable[node.index] = false;
    }
    else if (node.opcode == OR) {
        nullable[node.index] = (nullable[node.lfSon] | nullable[node.rgSon]);
    }
    else if (node.opcode == CAT) {
        nullable[node.index] = (nullable[node.lfSon] & nullable[node.rgSon]);
    }
    else if (node.opcode == STAR) {
        nullable[node.index] = true;
    }
}

void CalcFollowPos(const ExpTreeNode &node) {
    if (node.opcode == CAT) {
        std::for_each(lastPos[node.lfSon].begin(), lastPos[node.lfSon].end(), [&node](const int &last_of_lf) {
            followPos[last_of_lf] = Union(followPos[last_of_lf], firstPos[node.rgSon]);
        });
    }
    else if (node.opcode == STAR) {
        std::for_each(lastPos[node.lfSon].begin(), lastPos[node.lfSon].end(), [&node](const int &last) {
            followPos[last] = Union(followPos[last], firstPos[node.lfSon]);
        });
    }
}

void CalcDP(int index = root_node) {
    ExpTreeNode &node = nodeAt[index];

    int lfSon = node.lfSon;
    if (lfSon != -1) {
        CalcDP(lfSon);
    }

    int rgSon = nodeAt[index].rgSon;
    if (rgSon != -1) {
        CalcDP(rgSon);
    }

    CalcNullable(node);
    CalcFirstPos(node);
    CalcLastPos(node);
    CalcFollowPos(node);
};

class DFAEdge {
public:
    int index1, index2;
    char letter;

    bool operator <(const DFAEdge &other) const {
        if (index1 == other.index1) {
            if (index2 == other.index2) {
                return letter < other.letter;
            }

            return index2 < other.index2;
        }

        return index1 < other.index1;
    }

    bool operator ==(const DFAEdge &other) const {
        return index1 == other.index1 and index2 == other.index2 and letter == other.letter;
    }
};

std::string letterList;

void MakeLetterList(std::string RE) {
    std::for_each(RE.begin(), RE.end(), [](const char &ch) {
        if (IsLetter(ch)) {
            letterList.push_back(ch);
        }
    });

    sort(letterList.begin(), letterList.end());
    letterList.erase(std::unique(letterList.begin(), letterList.end()), letterList.end());
}

//DFA neighbour lists
std::vector<DFAEdge> DFA;
//list of final states
std::vector<int> finalStates;
//DFA will be constructed through a BFS
std::queue<int> q;
//list of expression tree nodes that dfa state represents
std::vector<int> TreeNodesIn[MaxN];
//number of dfa state that an array of three nodes represent
std::map<std::vector <int>, int> StateOf;
//number of states in DFA
int state_nr;

inline bool IsFinal(const int &node_ind) {
    std::vector<int> &nodes = TreeNodesIn[node_ind];
    auto found_it = std::find_if(nodes.begin(), nodes.end(), [&node_ind](const int &x) {
        //code of hashtag is one larger than codes of other letters
        return x == letter_nr - 1;
    });

    return found_it != nodes.end();
}

void MakeDFA() {
    TreeNodesIn[state_nr] = firstPos[root_node];
    StateOf[TreeNodesIn[state_nr]] = state_nr;
    q.push(state_nr);
    ++state_nr;

    while (q.size()) {
        int node_index = q.front();
        q.pop();

        std::for_each(letterList.begin(), letterList.end(), [&node_index](const char &edgeLetter) {
            std::vector<int> newState;
            std::for_each(TreeNodesIn[node_index].begin(), TreeNodesIn[node_index].end(),
                          [&node_index, &edgeLetter, &newState](const int &tree_node) {

                if (nodeAt[tree_node].letter == edgeLetter) {
                    newState = Union(newState, followPos[tree_node]);
                }
            });

            int nxt_index;
            if (!StateOf.count(newState)) {
                StateOf[newState] = state_nr;
                TreeNodesIn[state_nr] = newState;
                q.push(state_nr);
                nxt_index = state_nr;
                ++state_nr;
            } else {
                nxt_index = StateOf[newState];
            }

            DFAEdge newEdge;
            newEdge.letter = edgeLetter;
            newEdge.index1 = node_index;
            newEdge.index2 = nxt_index;
            DFA.push_back(newEdge);
        });

        if (IsFinal(node_index)) {
            finalStates.push_back(node_index);
        }
    }
}

void PrintDFA() {
    fout << state_nr << '\n';
    for (int i = 0; i < state_nr; ++i) {
        fout << i + 1 << ' ';
    }
    fout << '\n';

    fout << letterList.size() << '\n';
    std::for_each(letterList.begin(), letterList.end(), [](const char &ch) {
        fout << ch << ' ';
    });
    fout << '\n';

    fout << 1 << '\n';

    fout << finalStates.size() << '\n';
    std::for_each(finalStates.begin(), finalStates.end(),[](const int &x) {
        fout << x + 1 << ' ';
    });
    fout << '\n';

    std::sort(DFA.begin(), DFA.end());
    DFA.erase(std::unique(DFA.begin(), DFA.end()), DFA.end());

    fout << DFA.size() << '\n';
    std::for_each(DFA.begin(), DFA.end(), [](const DFAEdge &e) {
        fout << e.index1 + 1 << ' ' << e.letter << ' ' << e.index2 + 1 << '\n';
    });
}

int main() {
    std::string RE;
    fin >> RE;
    MakeLetterList(RE);

    std::string postfix_RE = ToPostfix(RE);
    MakeExpressionTree(postfix_RE);

    CalcDP();
    MakeDFA();
    PrintDFA();

    return 0;
}