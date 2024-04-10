#include <fstream>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

void part1() {
    ifstream input("input");
    set<int16_t> inset;

    int16_t i;
    while (input >> i) {
        if (inset.contains(2020 - i)) {
            cout << i * (2020 - i) << '\n';
            break;
        } else {
            inset.insert(i);
        }
    }
}

void part2() {
    ifstream input("input");
    set<int16_t> inset;
    vector<int16_t> invec;

    int16_t in;
    while (input >> in) {
        inset.insert(in);
        invec.push_back(in);
    }

    for (size_t i = 0; i < invec.size(); ++i) {
        bool find = false;
        for (size_t j = i; j < invec.size() - 1; ++j) {
            auto m = 2020 - invec[i] - invec[j];
            if (m == 0) {
                continue;
            }
            if (inset.contains(m)) {
                cout << invec[i] * invec[j] * m << '\n';
                find = true;
                break;
            }
        }
        if (find) {
            break;
        }
    }
}

int main() {
    part1();
    part2();
}