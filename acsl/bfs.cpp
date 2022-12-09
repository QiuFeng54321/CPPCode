#include <iostream>
#include <stack>

typedef int NodeType;
struct Node {
    NodeType value;
    Node* parent;
    Node* children[];
};

std::stack<Node*> stack;
int depth_count;

int main() {
    
}