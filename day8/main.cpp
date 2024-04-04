#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

struct node {
    string value;
    string lnodeVal;
    string rnodeVal;

    node* left;
    node* right;
};

static std::ifstream file("inputclean.txt");
static string steps;
static vector<node> nodes;
static node *head;

int search(string steps, int count, int index, node* currentNode) {
    node* next;
    if (steps[index] == 'R') {
        next = currentNode->right;
    } else {
        next = currentNode->left;
    }

    if (currentNode->value == "ZZZ") {
        return count;
    }
    ++index;
    index = (index % steps.size());
    return search(steps, ++count, index, next);
}

void solve() {
    file >> steps;

    string nodeVal, nodeL, nodeR;
    
    while(file >> nodeVal >> nodeL >> nodeR) {
        nodes.push_back(node{nodeVal, nodeL, nodeR});
    }

    for (node& n: nodes) {
        bool l = false, r = false;
        if (n.value == "AAA") head = &n;

        for (node &search: nodes) {
            if (l && r) break;
            if (n.lnodeVal == search.value) n.left = &search;
            if (n.rnodeVal == search.value) n.right = &search;
        }
    }
    
}

int main(){
    solve();
    int sum = search(steps, 0, 0, head);
    std::cout << steps.size() << "\n";
    std::cout << sum;
}

