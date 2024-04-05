#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <numeric>
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
static vector<node*> head_nodes;

int countSteps(string steps, int count, int index, node* currentNode) {
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
    return countSteps(steps, ++count, index, next);
}

uint64_t countMultiNodes(string steps, vector<node*> currentNodes) {
    vector<size_t> arrivalSteps(currentNodes.size());
    for (uint64_t i = 0; i < currentNodes.size(); ++i) {
        uint64_t k = 0;
        while (currentNodes[i]->value.back() != 'Z') {
            if (steps[k++ % steps.size()] == 'R') {
                currentNodes[i] = currentNodes[i]->right;
            } else {
                currentNodes[i] = currentNodes[i]->left;
            }
        }
        arrivalSteps[i] = k;
    }

    uint64_t c = 1;
    for (uint64_t i = 0; i < arrivalSteps.size(); ++i) {
        c = std::lcm(arrivalSteps[i], c);
    }

    return c;
}

void read() {
    file >> steps;

    string nodeVal, nodeL, nodeR;
    
    while(file >> nodeVal >> nodeL >> nodeR) {
        nodes.push_back(node{nodeVal, nodeL, nodeR});
    }

    for (node& n: nodes) {
        bool l = false, r = false;
        if (n.value == "AAA") head = &n;
        if (n.value.back() == 'A') head_nodes.push_back(&n);
        for (node &search: nodes) {
            if (l && r) break;
            if (n.lnodeVal == search.value) n.left = &search;
            if (n.rnodeVal == search.value) n.right = &search;
        }
    }
    
}

int main(){
    read();
    int sum = countSteps(steps, 0, 0, head);
    uint64_t sum2 = countMultiNodes(steps, head_nodes);
    std::cout << "part 1: " << sum << "\n";
    std::cout << "part 2: " << sum2 << "\n";
}

