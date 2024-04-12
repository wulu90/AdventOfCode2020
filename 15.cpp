#include <iostream>
#include <map>
#include <vector>
using namespace std;

void part1() {
    vector<int> vec{1, 17, 0, 10, 18, 11, 6};
    // vector<int> vec{3,1,2};
    auto start_num = vec.size();
    map<int, int> numinx;
    for (size_t i = 0; i < vec.size(); ++i) {
        numinx[vec[i]] = i;
    }
    vec.push_back(0);
    for (size_t i = start_num; i < 2020; ++i) {
        if (numinx.contains(vec[i])) {
            vec.push_back(i - numinx[vec[i]]);
            numinx[vec[i]] = i;
        } else {
            numinx[vec[i]] = i;
            vec.push_back(0);
        }
    }

    cout << vec[2019] << '\n';
}

void part2() {
    vector<int> vec{1, 17, 0, 10, 18, 11, 6};
    // vector<int> vec{3, 1, 2};
    map<int, int> numinx;
    for (size_t i = 0; i < vec.size() - 1; ++i) {
        numinx[vec[i]] = i + 1;
    }
    int curr = vec.back();

    for (int i = vec.size() + 1; i <= 30000000; ++i) {
        if (numinx.contains(curr)) {
            int last     = numinx[curr];
            numinx[curr] = i - 1;

            curr = i - 1 - last;

        } else {
            numinx[curr] = i - 1;
            curr         = 0;
        }
    }

    cout << curr << '\n';
}

int main() {
    part1();
    part2();
    return 0;
}