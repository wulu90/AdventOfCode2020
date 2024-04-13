#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;

int active_neighbours(const set<tuple<int, int, int>>& active_coords, int x, int y, int z) {
    static vector<tuple<int, int, int>> nei{{-1, -1, -1}, {-1, -1, 0}, {-1, -1, 1}, {-1, 0, -1}, {-1, 0, 0}, {-1, 0, 1}, {-1, 1, -1},
                                            {-1, 1, 0},   {-1, 1, 1},  {0, -1, -1}, {0, -1, 0},  {0, -1, 1}, {0, 0, -1}, {0, 0, 1},
                                            {0, 1, -1},   {0, 1, 0},   {0, 1, 1},   {1, -1, -1}, {1, -1, 0}, {1, -1, 1}, {1, 0, -1},
                                            {1, 0, 0},    {1, 0, 1},   {1, 1, -1},  {1, 1, 0},   {1, 1, 1}};

    int re = 0;
    for (auto [a, b, c] : nei) {
        if (active_coords.contains({x + a, y + b, z + c})) {
            ++re;
        }
    }
    return re;
}

void part1() {
    ifstream input("input");
    vector<string> inmap;
    for (string line; getline(input, line);) {
        inmap.push_back(line);
    }

    set<tuple<int, int, int>> active_coords;

    for (auto it = inmap.rbegin(); it != inmap.rend(); ++it) {
        for (size_t j = 0; j < it->size(); ++j) {
            if ((*it)[j] == '#') {
                active_coords.insert({it - inmap.rbegin(), j, 0});
            }
        }
    }

    int x1 = -1, x2 = inmap[0].size(), y1 = -1, y2 = inmap.size(), z1 = -1, z2 = 1;

    for (int c = 1; c <= 6; ++c) {
        set<tuple<int, int, int>> tmp;

        for (int x = x1; x <= x2; ++x) {
            for (int y = y1; y <= y2; ++y) {
                for (int z = z1; z <= z2; ++z) {
                    auto ac = active_neighbours(active_coords, x, y, z);
                    if (active_coords.contains({x, y, z})) {    // cube active
                        if (ac == 2 || ac == 3) {
                            tmp.insert({x, y, z});
                        }
                    } else {
                        if (ac == 3) {
                            tmp.insert({x, y, z});
                        }
                    }
                }
            }
        }

        --x1;
        ++x2;
        --y1;
        ++y2;
        --z1;
        ++z2;
        active_coords = tmp;
    }

    cout << active_coords.size() << '\n';
}

int main() {
    part1();
    return 0;
}