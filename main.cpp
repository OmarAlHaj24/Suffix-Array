#include <iostream>
#include <algorithm>

using namespace std;

class Node {
public:
    char data;
    int idx;
    int r1;
    int r2;
    int prevR;

    Node() {
        data = ' ';
        idx = -1;
        r1 = 0;
        r2 = 0;
    }

    Node(char d, int i) {
        data = d;
        idx = i;
        r1 = 0;
        r2 = 0;
        prevR = 0;
    }

    friend bool charComp(Node a, Node b);

    friend bool rComp(Node a, Node b);

    friend bool idxComp(Node a, Node b);
};

bool charComp(Node a, Node b) {
    if (a.data < b.data) {
        return true;
    }
    return false;
}

bool rComp(Node a, Node b) {
    if (a.r1 < b.r1) {
        return true;
    } else if (a.r1 == b.r1 && a.r2 < b.r2) {
        return true;
    }
    return false;
}

bool idxComp(Node a, Node b) {
    if (a.idx < b.idx) {
        return true;
    }
    return false;
}

class SuffixArray {
    Node *nodes;
    int sz = 0;
public:
    SuffixArray(string txt) {
        sz = txt.size();
        nodes = new Node[sz];
        for (int i = 0; i < sz; i++) {
            nodes[i] = *new Node(txt[i], i);
        }
    }

    void ConstructUsingPrefixDoubling() {
        int cnt = 0;
        int itCnt = 1;
        sort(nodes, nodes + sz, charComp);
        for (int i = 1; i < sz; i++) {
            if (nodes[i].data > nodes[i - 1].data) {
                nodes[i].r1 = ++cnt;
            } else {
                nodes[i].r1 = cnt;
            }
        }
        bool flag = false;
        while (true) {
            sort(nodes, nodes + sz, idxComp);
            for (int i = 0; i < sz - itCnt; i++) {
                nodes[i].r2 = nodes[i + itCnt].r1;
                nodes[i].prevR = nodes[i].r1;
            }
            for (int i = sz - itCnt; i < sz; i++) {
                nodes[i].r2 = 0;
                nodes[i].prevR = nodes[i].r1;
            }
            sort(nodes, nodes + sz, rComp);

            for (int i = 1; i < sz; i++) {
                nodes[i].prevR = nodes[i].r1;
                if (nodes[i].r1 == nodes[i - 1].prevR && nodes[i].r2 == nodes[i - 1].r2) {
                    nodes[i].r1 = nodes[i - 1].r1;
                } else {
                    nodes[i].r1 = nodes[i - 1].r1 + 1;
                    if (nodes[i].r1 == sz - 1)
                        flag = true;
                }
            }
            if (flag) {
                break;
            }
            itCnt = itCnt * 2;
        }
    }

    void Print() {
        sort(nodes, nodes + sz, rComp);
        for (int i = 0; i < sz; i++) {
            cout << nodes[i].idx << " ";
        }
    }
};

int main() {
    SuffixArray t("ACGACTACGATAAC$");

    t.ConstructUsingPrefixDoubling();

    t.Print(); // Prints:  14 11 12  0  6  3  9 13  1  7  4  2  8 10  5

    return 0;
}