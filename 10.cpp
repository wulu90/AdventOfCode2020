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

int main() {
    part1();
    return 0;
}