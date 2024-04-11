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

int main() {
    part1();
    return 0;
}
