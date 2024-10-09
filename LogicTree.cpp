#include "LogicTree.h"

void LogicTree::_clear(Node* node)
{
    if (node == nullptr) {
        return;
    }

    _clear(node->left);
    _clear(node->right);
    delete node;
}

bool LogicTree::_calc(Node* node, bool val)
{
    if (node->ch == 't') {
        return node->val = true;
    }

    if (node->ch == 'f') {
        return node->val = false;
    }

    if (node->ch == 'x') {
        return node->val = val;
    }

    if (node->ch == '!') {
        _calc(node->right, val);
        return node->val = !node->right->val;
    }

    if (node->ch == '|') {
        _calc(node->left, val);
        _calc(node->right, val);
        return node->val = node->left->val || node->right->val;
    }

    _calc(node->left, val);
    _calc(node->right, val);
    return node->val = node->left->val && node->right->val;
}

void LogicTree::_print(Node* node, int pos)
{
    vector<vector<char>> res(200, vector<char>(2 * pos + 100, ' '));
    int maxr = 0;
    _printNode(res, node, 0, 0, 2 * pos, maxr);

    for (int i = 0; i <= maxr; ++i) {
        for (int j = 0; j < res[i].size(); ++j) {
            cout << res[i][j];
        }

        cout << '\n';
    }
}

void LogicTree::_printNode(vector<vector<char>>& res, Node* node, int r, int left ,int right, int& maxr)
{
    int pos = (left + right) / 2;
    res[r][pos] = node->ch;

    maxr = std::max(r, maxr);

    if (node->left != nullptr) {
        _printNode(res, node->left, r + 1, left, pos, maxr);
    }

    if (node->right != nullptr) {
        _printNode(res, node->right, r + 1, pos, right, maxr);
    }
}

LogicTree::LogicTree(const string& s)
{
    _root = new Node();
    Node* cur(_root);

    for (int i = s.size() - 1; i >= 0; --i) {
        if (s[i] == '!' || s[i] == '&' || s[i] == '|') {
            cur->ch = s[i];
            Node* newNode = new Node();
            cur->right = newNode;
            newNode->prev = cur;
            cur = newNode;
        }
        else {
            cur->ch = s[i];
            cur = cur->prev;

            while (cur->prev != nullptr && (cur->ch == '!' || cur->left != nullptr)) {
                cur = cur->prev;
            }

            if (cur->left == nullptr) {
                Node* newNode = new Node();
                cur->left = newNode;
                newNode->prev = cur;
                cur = newNode;
            }
        }
    }
}

LogicTree::~LogicTree()
{
    _clear(_root);
}

bool LogicTree::calc(bool val)
{
    return _calc(_root, val);
}

void LogicTree::print(int pos)
{
    _print(_root, pos);
}
