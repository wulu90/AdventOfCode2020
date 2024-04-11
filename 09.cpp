#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
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

void part2() {
    ifstream input("input");
    vector<int64_t> xmas;
    for (int64_t t; input >> t;) {
        xmas.push_back(t);
    }

    int64_t weakness = 1930745883;

    vector<int64_t> sumvec;
    map<int64_t, size_t> sum_index;

    int64_t sum = 0;
    for (size_t i = 0; i < xmas.size(); ++i) {
        sum += xmas[i];
        sumvec.push_back(sum);
        sum_index.insert({sum, i});
    }

    size_t l = 0;
    size_t r = 0;
    for (size_t i = 0; i < xmas.size(); ++i) {
        if (sum_index.contains(sumvec[i] - weakness)) {
            l = sum_index[sumvec[i] - weakness];
            r = i;
            break;
        }
    }

    auto [min, max] = minmax_element(xmas.begin() + l + 1, xmas.begin() + r + 1);
    cout << *min + *max << '\n';
}

int main() {
    part1();
    part2();
    return 0;
}