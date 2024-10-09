//Вариант 10.
//Написать программу, преобразующую логическое выражение, допускающее скобочную запись, 
//операции &&, ||, !, логические константы и переменную x, в бинарное дерево, 
//структурно эквивалентное выражению. Реализовать функцию вычисления выражения по дереву 
//для заданного x.
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include "LogicTree.h"

using std::string;
using std::cin;
using std::cout;
using std::stack;

void normalize(std::string& s) {
	string res;

	for (int i = 0; i < s.size(); ++i) {
		s[i] = tolower(s[i]);
	}

	for (int i = 0; i < s.size(); ++i) {
		if (isalpha(s[i])) {
			if (s[i] == 'x') {
				res.push_back(s[i]);
			}
			else if (s[i] == 't' || s[i] == 'f') {
				if (i == 0 || !isalpha(s[i - 1])) {
					res.push_back(s[i]);
				}
			}
		}
		else {
			if (s[i] == '|' || s[i] == '&') {
				if (i == 0 || s[i] != s[i - 1]) {
					res.push_back(s[i]);
				}
			}
			else {
				res.push_back(s[i]);
			}
		}
	}

    string res2;

    for (char c : res) {
        if (c != ' ') {
            res2.push_back(c);
        }
    }

    s = res2;
}

int priority(char c) {
    if (c == '!') {
        return 3;
    }

    if (c == '&') {
        return 2;
    }

    return 1;
}

void processOperation(stack<string>& st, char op) {
    if (op == '!') {
        string res = st.top();
        st.pop();
        res += '!';
        st.push(res);
    }
    else {
        string right = st.top();
        st.pop();
        string left = st.top();
        st.pop();
        string res = left + right;
        res.push_back(op);
        st.push(res);
    }
}

std::string reversedPolishNotation(const std::string& s) {
    stack<string> st;
    stack<char> op;

    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '(') {
            op.push('(');
        }
        else if (s[i] == ')') {
            while (op.top() != '(') {
                processOperation(st, op.top());
                op.pop();
            }

            op.pop();
        }
        else if (s[i] == 'f' || s[i] == 't' || s[i] == 'x') {
            string tmp;
            tmp.push_back(s[i]);
            st.push(tmp);
        }
        else {
            while (op.size() > 0 && op.top() != '(' && priority(s[i]) <= priority(op.top())) {
                processOperation(st, op.top());
                op.pop();
            }

            op.push(s[i]);
        }
    }

    while (op.size() > 0) {
        processOperation(st, op.top());
        op.pop();
    }

    return st.top();
}

int main() {
	string s;
	getline(cin, s);
	normalize(s);
    s = reversedPolishNotation(s);

    LogicTree tr(s);
    cout << "x == True: " << (tr.calc(true) ? "True" : "False") << '\n';
    cout << "x == False: " << (tr.calc(false) ? "True" : "False") << '\n';
    cout << "\n\n\n";
    tr.print(32);
}