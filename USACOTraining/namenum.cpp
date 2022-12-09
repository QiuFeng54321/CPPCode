/*
ID: william234
TASK: namenum
LANG: C++
*/
/* LANG can be C++11 or C++14 for those more recent releases */
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <string>

using namespace std;
struct Node
{
    int chr;
    bool isCompleteWord;
    Node *parent = nullptr;
    map<int, Node *> nodes;
};
Node *root = new Node;
queue<Node *> q;
string dict = "ABCDEFGHIJKLMNOPRSTUVWXY";
int main()
{
    ofstream fout("namenum.out");
    ifstream fin("namenum.in");
    ifstream dictin("dict.txt");
    while (!dictin.eof())
    {
        string s;
        dictin >> s;
        auto currentNode = root;
        for (auto c : s)
        {
            auto key = dict.find(c);
            if (currentNode->nodes.find(key) == currentNode->nodes.end())
            {
                Node *child = new Node;
                child->chr = key;
                child->parent = currentNode;
                currentNode->nodes[key] = child;
                currentNode = child;
                // fout << '*';
            }
            else
            {
                currentNode = currentNode->nodes[key];
            }
            // fout << c;
            // fout << endl;
        }
        currentNode->isCompleteWord = true;
    }
    string code;
    fin >> code;
    q.push(root);
    for (auto c : code)
    {
        auto key = (c - '2') * 3;
        cout << '-' << c << '-' << key << '-';
        auto size = q.size();
        for (auto i = 0; i < size; i++)
        {
            auto previousNode = q.front();
            q.pop();
            for (auto child : previousNode->nodes)
            {
                cout << child.first << "(" << dict[child.first] << ")";
                auto diff = child.first - key;
                if (diff >= 0 && diff < 3)
                {
                    q.push(child.second);
                    cout << "< ";
                }
            }
            cout << endl;
        }
    }
    auto size = q.size();
    if (size == 0) {
        fout << "NONE" << endl;
    }
    for (auto i = 0; i < size; i++)
    {
        auto last = q.front();
        q.pop();
        if (!last->isCompleteWord) continue;
        string res = "";
        while (last->parent != nullptr)
        {
            res.insert(res.begin(), dict[last->chr]);
            last = last->parent;
        }
        fout << res << endl;
    }
    return 0;
}