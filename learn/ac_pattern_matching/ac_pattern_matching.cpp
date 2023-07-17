#include <iostream>
#include <map>
#include <string>
#include <vector>

struct Node {
    std::map<char, Node*> children;
    Node* fail = nullptr;
    Node* parent = nullptr;
    bool accept = false;
    char fromChar;
    std::string acceptStr;
    void add(std::string str) {
        Node* curr = this;
        for (char c : str) {
            if (curr->children.find(c) == curr->children.end()) {
                curr->children[c] = new Node();
                curr->children[c]->parent = curr;
                curr->children[c]->fromChar = c;
            }
            curr = curr->children[c];
        }
        curr->accept = true;
        curr->acceptStr = str;
    }
    void generateFail(Node* root) {
        if (parent == nullptr || parent->parent == nullptr) {
            fail = root;
        } else if (fail == nullptr) {
            auto curr = parent->fail;
            while (curr->parent != nullptr &&
                   curr->children.find(fromChar) == curr->children.end()) {
                curr = curr->fail;
                assert(curr);
            }
            if (curr->children.find(fromChar) == curr->children.end()) {
                fail = root;
            } else {
                fail = curr->children[fromChar];
                fail->generateFail(root);
            }
            // if (curr->children.find(fromChar) != curr->children.end()) {
            //     fail = curr->children[fromChar];
            // } else {
            //     fail = curr;
            // }
        }
        for (const auto& [c, child] : children) {
            child->generateFail(root);
        }
    }
    void search(std::string str,
                std::vector<std::pair<int, std::string>>& res) {
        Node* curr = this;
        const int n = str.size();
        for (int i = 0; i < n; i++) {
            const char& c = str[i];
            std::cout << "Consume " << c << " at " << i << ": ";
            bool pass = false;
            while (curr->children.find(c) == curr->children.end()) {
                std::cout << "Fail: " << i << ": " << c << ";";
                if (curr == this) {
                    pass = true;
                    std::cout << std::endl;
                    break;
                }
                curr = curr->fail;
                assert(curr);
            }
            if (pass) continue;
            curr = curr->children[c];
            if (curr->accept) {
                const auto startIdx = i - curr->acceptStr.size() + 1;
                std::cout << "Accept: " << curr->acceptStr << " at "
                          << startIdx;
                res.push_back(std::make_pair(startIdx, curr->acceptStr));
            }
            std::cout << std::endl;
        }
    }
};

// test
#include <fstream>
int main() {
    std::ifstream fin("test1.in");
    std::string searchText;
    int n;
    fin >> searchText;
    fin >> n;
    std::vector<std::string> patterns(n);
    for (int i = 0; i < n; i++) {
        fin >> patterns[i];
    }

    Node* root = new Node();
    for (const auto& s : patterns) {
        root->add(s);
    }
    root->generateFail(root);
    std::vector<std::pair<int, std::string>> res;
    root->search(searchText, res);
    for (const auto& p : res) {
        std::cout << p.first << " " << p.second << std::endl;
    }
    return 0;
}