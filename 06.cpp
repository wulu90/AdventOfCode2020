#include <fstream>
#include <iostream>
#include <set>
#include <string>

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

int main() {
    part1();
    return 0;
}