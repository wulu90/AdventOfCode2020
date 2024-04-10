#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void part1() {
    ifstream input("input");
    string line;
    vector<string> strvec;

    while (getline(input, line)) {
        strvec.push_back(line);
    }

    int row = strvec.size();
    int col = strvec.begin()->size();

    int i     = 0;
    int j     = 0;
    int trees = 0;
    while (i < row) {
        if (strvec[i][j] == '#') {
            ++trees;
        }
        ++i;
        j += 3;
        if (j >= col) {
            j -= col;
        }
    }

    cout << trees << '\n';
}

void part2() {
    ifstream input("input");
    string line;
    vector<string> strvec;

    while (getline(input, line)) {
        strvec.push_back(line);
    }

    int row = strvec.size();
    int col = strvec.begin()->size();

    vector<pair<int, int>> slopes{{1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}};

    vector<vector<pair<int, int>>> posvec;

    for (size_t n = 0; n < slopes.size(); ++n) {
        int i = 0;
        int j = 0;
        vector<pair<int, int>> pos;
        while (i < row) {
            pos.push_back({i, j});
            i += slopes[n].second;
            j += slopes[n].first;
            if (j >= col) {
                j -= col;
            }
        }

        posvec.push_back(pos);
    }

    int64_t re = 1;
    for (size_t n = 0; n < posvec.size(); ++n) {
        int count = 0;
        for (auto [i, j] : posvec[n]) {
            if (strvec[i][j] == '#') {
                ++count;
            }
        }

        re *= count;
    }

    cout << re << '\n';
}

int main() {
    part1();
    part2();
    return 0;
}