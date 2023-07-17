#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
using namespace std;

const char NODE = 'N', NONE = 'x';

struct Node {
    string val;
    Node *left, *right;
    Node(string val, Node* left = nullptr, Node* right = nullptr)
        : val(val), left(left), right(right) {}
};

void write(stringstream& ss, Node* node) {
    if (node == nullptr) {
        ss << NONE;
    } else {
        ss << NODE;
        int len = node->val.size();
        ss.write((const char*)&len, sizeof(len));
        ss << node->val;
    }
}

Node* read(stringstream& ss) {
    char type;
    ss >> type;
    if (type == NONE) return nullptr;
    int len;
    ss.read((char*)&len, sizeof(len));
    char c[len];
    ss.read(c, sizeof(c));
    string val = string(c, sizeof(c));
    return new Node(val, read(ss), read(ss));
}

string serialize(Node* root) {
    stack<Node*> stk ;
    stringstream ss;
    stk.push(root);

    while (!stk.empty()) {
        auto node = stk.top();
        stk.pop();
        write(ss, node);
        if (node != nullptr) {
            stk.push(node->right);
            stk.push(node->left);
        }
    }
    return ss.str();
}

Node* deserialize(string str) {
    stringstream ss(str);
    return read(ss);
}

int main() {
    auto root = new Node("root", new Node("left", new Node("left.left")), new Node("right"));
    auto ser = serialize(root);
    cout << ser << endl;
    auto des = deserialize(ser);
    assert(root->left->left->val == des->left->left->val);
}