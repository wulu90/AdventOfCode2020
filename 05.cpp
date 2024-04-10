#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

int seatindex(int lower, int upper, const string_view& str) {
    int i = 0;
    while (lower + 1 < upper) {
        auto mid = (lower + upper) / 2;
        if (str[i] == 'F' || str[i] == 'L') {
            upper = mid;
        } else {
            lower = mid + 1;
        }
        ++i;
    }

    return (str[i] == 'F' || str[i] == 'L') ? lower : upper;
}

void part1() {
    ifstream input("input");
    string line;

    int maxid = 0;
    while (getline(input, line)) {
        int seatid = seatindex(0, 127, string_view{line.data(), 7}) * 8 + seatindex(0, 7, {line.data() + 7, 3});

        maxid = max(maxid, seatid);
    }

    cout << maxid << '\n';
}

void part2() {
    ifstream input("input");
    string line;
    vector<int> idvec;

    while (getline(input, line)) {
        int seatid = seatindex(0, 127, string_view{line.data(), 7}) * 8 + seatindex(0, 7, {line.data() + 7, 3});
        idvec.push_back(seatid);
    }

    sort(idvec.begin(), idvec.end());

    for (size_t i = 1; i < idvec.size(); ++i) {
        if (idvec[i] != idvec[i - 1] + 1) {
            cout << idvec[i] - 1 << '\n';
            break;
        }
    }
}

int main() {
    part1();
    part2();
    return 0;
}