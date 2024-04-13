#include <fstream>
#include <iostream>
#include <stack>
#include <string>

using namespace std;

int64_t calc(const string& str, size_t l, size_t r) {
    int64_t ans  = 0;
    int64_t curr = 0;
    char op;
    bool hasop = false;
    for (size_t i = l; i < r; ++i) {
        auto c = str[i];
        if (isdigit(c)) {
            curr = 0;
            while (isdigit(str[i])) {
                curr = curr * 10 + str[i] - '0';
                ++i;
            }
            --i;

            if (hasop) {
                if (op == '+') {
                    ans += curr;
                } else if (op == '*') {
                    ans *= curr;
                }
            } else {
                ans = curr;
            }

        } else if (isspace(c)) {
            continue;
        } else {
            if (c == '+' || c == '*') {
                op    = c;
                hasop = true;
            } else {
                if (c == '(') {
                    int lb = 1;
                    for (size_t j = i + 1; j < r; ++j) {
                        if (str[j] == '(') {
                            ++lb;
                        } else if (str[j] == ')') {
                            --lb;
                            if (lb == 0) {
                                curr = calc(str, i, j);
                                i    = j + 1;

                                if (hasop) {
                                    if (op == '+') {
                                        ans += curr;
                                    } else if (op == '*') {
                                        ans *= curr;
                                    }
                                } else {
                                    ans = curr;
                                }

                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    return ans;
}

void part1() {
    ifstream input("input");
    int64_t ans = 0;
    for (string line; getline(input, line);) {
        ans += calc(line, 0, line.size());
    }

    cout << ans << '\n';
}

int main() {
    part1();
    return 0;
}