#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

void part1() {
    ifstream input("input");
    vector<int64_t> xmas;
    for (int64_t t; input >> t;) {
        xmas.push_back(t);
    }

    set<int64_t> preamble;
    for (size_t i = 0; i < 25; ++i) {
        preamble.insert(xmas[i]);
    }

    for (size_t i = 25; i < xmas.size(); ++i) {
        auto sum   = xmas[i];
        bool valid = false;

        if (i > 25) {
            preamble.erase(xmas[i - 25 - 1]);
            preamble.insert(xmas[i - 1]);
        }

        for (size_t j = i - 25; j < i; ++j) {
            if (preamble.contains(sum - xmas[j])) {
                valid = true;
                break;
            }
        }

        if (!valid) {
            cout << sum << '\n';
            break;
        }
    }
}

int main() {
    part1();
    return 0;
}