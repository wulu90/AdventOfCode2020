#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <string>
#include <vector>
using namespace std;

void part1() {
    ifstream input("input");
    string line;
    set<char> yes_questions;
    int count = 0;
    while (input.good()) {
        getline(input, line);
        if (line.empty() || input.eof()) {
            count += yes_questions.size();
            yes_questions.clear();
        } else {
            for (auto c : line) {
                yes_questions.insert(c);
            }
        }
    }
    cout << count << '\n';
}

void part1_bit() {
    ifstream input("input");
    string line;
    vector<u_int32_t> groupans;
    int count = 0;
    while (input.good()) {
        getline(input, line);
        if (line.empty() || input.eof()) {
            auto anyone_ans = ranges::fold_left_first(groupans.begin(), groupans.end(), bit_or<u_int32_t>());
            count += popcount(anyone_ans.value());

            groupans.clear();

        } else {
            u_int32_t answers = 0;
            for (auto c : line) {
                answers |= 1 << (c - 'a');
            }
            groupans.push_back(answers);
        }
    }

    cout << count << '\n';
}

void part2() {
    ifstream input("input");
    string line;
    vector<u_int32_t> groupans;
    int count = 0;
    while (input.good()) {
        getline(input, line);
        if (line.empty() || input.eof()) {
            auto everyans = ranges::fold_left_first(groupans.begin(), groupans.end(), bit_and<u_int32_t>());
            count += popcount(everyans.value());

            groupans.clear();

        } else {
            u_int32_t answers = 0;
            for (auto c : line) {
                answers |= 1 << (c - 'a');
            }
            groupans.push_back(answers);
        }
    }

    cout << count << '\n';
}

int main() {
    part1_bit();
    part2();
    return 0;
}