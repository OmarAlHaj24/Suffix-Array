#include <iostream>
#include <algorithm>
using namespace std;

struct Node{
    char data;
    int idx;
    int r1;
    int r2;

public:
    Node(char d, int i){
        data = d;
        idx = i;
        r1 = 0;
        r2 = 0;
    }
};

class SuffixArray{
    Node* []nodes;
public:
    SuffixArray(String txt){
        nodes = new Node[txt.size];

};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
