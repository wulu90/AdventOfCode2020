#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

void part1() {
    ifstream input("input");
    vector<int> adaptervec;
    for (int i = 0; input >> i;) {
        adaptervec.push_back(i);
    }

    sort(adaptervec.begin(), adaptervec.end());

    map<int, int> diff_num;

    int currate = 0;
    for (size_t i = 0; i < adaptervec.size(); ++i) {
        ++diff_num[adaptervec[i] - currate];
        currate = adaptervec[i];
    }

    ++diff_num[3];

    cout << diff_num[1] * diff_num[3] << '\n';
}

void part2() {
    ifstream input("input");
    vector<int> adaptervec;
    for (int i = 0; input >> i;) {
        adaptervec.push_back(i);
    }

    sort(adaptervec.begin(), adaptervec.end(), greater<int>());

    vector<int64_t> dp(adaptervec.size() + 1, 0l);

    dp.front() = 1;

    for (size_t i = 0; i < dp.size(); ++i) {
        for (size_t j = 1; j <= 3; ++j) {
            if (adaptervec[i + j] >= adaptervec[i] - 3) {
                dp[i + j] += dp[i];
            }
        }
    }

    cout << dp.back() << '\n';
}

int main() {
    part1();
    part2();
    return 0;
}