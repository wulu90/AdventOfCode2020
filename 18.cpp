#include <fstream>
#include <functional>
#include <iostream>
#include <stack>
#include <string>

using namespace std;

int64_t calc(char op, int64_t l, int64_t r) {
    if (op == '+')
        return l + r;
    else if (op == '*')
        return l * r;
    return -1;
}

int64_t precedence(char op) {
    int64_t p = 0;
    switch (op) {
    case '+':
    case '*':
        p = 1;
        break;
        // case '(':
        // case ')':
        //     p = 2;
    }
    return p;
}

int64_t precedence2(char op) {
    int64_t p = 0;
    switch (op) {
    case '+':
        p = 2;
        break;
    case '*':
        p = 1;
        break;
        // case '(':
        // case ')':
        //     p = 2;
    }
    return p;
}

// https://en.wikipedia.org/wiki/Shunting_yard_algorithm
// https://github.com/somyalalwani/generic-calculator-using-stack/blob/main/code.cpp
// https://stackoverflow.com/questions/64744819/stack-calculator has a error , () precedence should be 0 or -1.

void process(stack<int64_t>& operator_stack, stack<char>& operand_stack) {
    int64_t r = operator_stack.top();
    operator_stack.pop();
    int64_t l = operator_stack.top();
    operator_stack.pop();
    int64_t re = calc(operand_stack.top(), l, r);
    operand_stack.pop();
    operator_stack.push(re);
}

int64_t getvalue(const string& str, function<int64_t(char)> precedence) {
    stack<char> operand_stack;
    stack<int64_t> operator_stack;

    for (size_t i = 0; i < str.size(); ++i) {
        if (isdigit(str[i])) {
            int64_t n = 0;
            while (isdigit(str[i])) {
                n = n * 10 + str[i] - '0';
                ++i;
            }
            --i;

            operator_stack.push(n);
        } else if (str[i] == ' ') {
            continue;
        } else if (str[i] == '(') {
            operand_stack.push('(');
        } else if (str[i] == ')') {
            while (operand_stack.top() != '(') {
                process(operator_stack, operand_stack);
            }
            operand_stack.pop();
        } else if (str[i] == '+' || str[i] == '*') {
            int64_t cp = precedence(str[i]);
            while (!operand_stack.empty() && precedence(operand_stack.top()) >= cp) {
                process(operator_stack, operand_stack);
            }
            operand_stack.push(str[i]);
        }
    }

    while (!operand_stack.empty()) {
        process(operator_stack, operand_stack);
    }

    return operator_stack.top();
}

void part1() {
    ifstream input("input");
    int64_t ans = 0;
    for (string line; getline(input, line);) {
        ans += getvalue(line, precedence);
    }

    cout << ans << '\n';
}

void part2() {
    ifstream input("input");
    int64_t ans = 0;
    for (string line; getline(input, line);) {
        ans += getvalue(line, precedence2);
    }

    cout << ans << '\n';
}

int main() {
    part1();
    part2();
    return 0;
}