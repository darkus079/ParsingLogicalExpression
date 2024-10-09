#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <queue>
#include <vector>

using std::vector;
using std::string;
using std::cout;

class LogicTree {
private:
    struct Node {
        Node* left;
        Node* right;
        Node* prev;
        char ch;
        bool val;

        Node() : left(nullptr), right(nullptr), prev(nullptr), ch(0), val(false) { }
    };

    Node* _root;
    void _clear(Node* node);
    bool _calc(Node* node, bool val);
    void _print(Node* node, int pos);
    void _printNode(vector<vector<char>>& res, Node* node, int r, int left, int right, int& maxr);

public:
    LogicTree() : _root(new Node()) { }
    LogicTree(const string& s);
    ~LogicTree();
    bool calc(bool val);
    void print(int pos);
};