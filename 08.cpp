#include <charconv>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum class operation { acc, jmp, nop };

struct instruction {
    operation op;
    int arg;

    instruction(const string& str) {
        if (str.starts_with("acc")) {
            op = operation::acc;
        } else if (str.starts_with("jmp")) {
            op = operation::jmp;
        } else {
            op = operation::nop;
        }

        from_chars(str.data() + 5, str.data() + str.length(), arg);
        arg = str[4] == '+' ? arg : -arg;
    }
};

void part1() {
    ifstream input("input");
    string line;
    vector<instruction> ins;
    while (getline(input, line)) {
        ins.emplace_back(line);
    }

    vector<int> exetime(ins.size(), 0);

    int accumulator  = 0;
    size_t ins_index = 0;
    while (true) {
        if (exetime[ins_index] == 1) {
            break;
        }

        ++exetime[ins_index];
        auto [op, arg] = ins[ins_index];
        switch (op) {
        case operation::acc:
            accumulator += arg;
            ++ins_index;
            break;
        case operation::jmp:
            ins_index += arg;
            break;
        default:
            ++ins_index;
            break;
        }
    }

    cout << accumulator << '\n';
}

void part2() {
    ifstream input("input");
    string line;
    vector<instruction> ins;
    while (getline(input, line)) {
        ins.emplace_back(line);
    }

    vector<size_t> jmp_nop_inx;
    for (size_t i = 0; i < ins.size(); ++i) {
        if (ins[i].op == operation::jmp || ins[i].op == operation::nop) {
            jmp_nop_inx.push_back(i);
        }
    }
    for (size_t i = 0; i < jmp_nop_inx.size(); ++i) {
        int accumulator  = 0;
        size_t ins_index = 0;
        vector<int> exetime(ins.size(), 0);
        size_t tobechanged = jmp_nop_inx[i];
        bool terminate     = false;
        while (true) {
            if (ins_index == ins.size()) {
                terminate = true;
                break;
            }

            if (exetime[ins_index] == 1) {    // loop
                break;
            }

            ++exetime[ins_index];

            auto [op, arg] = ins[ins_index];
            switch (op) {
            case operation::acc:
                accumulator += arg;
                ++ins_index;
                break;
            case operation::jmp:
                if (ins_index == tobechanged) {    // jmp -> nop
                    ++ins_index;
                } else {
                    ins_index += arg;
                }
                break;
            default:
                if (ins_index == tobechanged) {    // nop -> jmp
                    ins_index += arg;
                } else {
                    ++ins_index;
                }
                break;
            }
        }

        if (terminate) {
            cout << accumulator << '\n';
            break;
        }
    }
}

int main() {
    part1();
    part2();
    return 0;
}
