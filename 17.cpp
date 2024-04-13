#include <array>
#include <fstream>
#include <iostream>
#include <queue>
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

int active_neighbours_4d(const set<tuple<int, int, int, int>>& active_coords_4d, const set<tuple<int, int, int, int>>& nei4d, int x, int y,
                         int z, int w) {
    int re = 0;
    for (auto [a, b, c, d] : nei4d) {
        if (active_coords_4d.contains({x + a, y + b, z + c, w + d})) {
            ++re;
        }
    }
    return re;
}

void part2() {
    ifstream input("input");
    vector<string> inmap;
    for (string line; getline(input, line);) {
        inmap.push_back(line);
    }

    set<tuple<int, int, int, int>> active_coords_4d;

    for (auto it = inmap.rbegin(); it != inmap.rend(); ++it) {
        for (size_t j = 0; j < it->size(); ++j) {
            if ((*it)[j] == '#') {
                active_coords_4d.insert({it - inmap.rbegin(), j, 0, 0});
            }
        }
    }

    int x1 = -1, x2 = inmap[0].size(), y1 = -1, y2 = inmap.size(), z1 = -1, z2 = 1, w1 = -1, w2 = 1;

    queue<array<int, 4>> q;
    q.push({0, 0, 0, 0});

    for (int i = 0; i < 4; ++i) {
        auto n = q.size();
        for (size_t j = 0; j < n; ++j) {
            auto arr1 = q.front();
            auto arr2 = q.front();
            auto arr3 = q.front();

            arr1[i] += 1;
            arr2[i] += 0;
            arr3[i] += -1;

            q.push(arr1);
            q.push(arr2);
            q.push(arr3);

            q.pop();
        }
    }

    set<tuple<int, int, int, int>> nei4d;
    while (!q.empty()) {
        auto [x, y, z, w] = q.front();
        nei4d.insert({x, y, z, w});
        q.pop();
    }
    nei4d.erase({0, 0, 0, 0});

    for (int c = 1; c <= 6; ++c) {
        set<tuple<int, int, int, int>> tmp;

        for (int x = x1; x <= x2; ++x) {
            for (int y = y1; y <= y2; ++y) {
                for (int z = z1; z <= z2; ++z) {
                    for (int w = w1; w <= w2; ++w) {
                        auto ac = active_neighbours_4d(active_coords_4d, nei4d, x, y, z, w);
                        if (active_coords_4d.contains({x, y, z, w})) {    // cube active
                            if (ac == 2 || ac == 3) {
                                tmp.insert({x, y, z, w});
                            }
                        } else {
                            if (ac == 3) {
                                tmp.insert({x, y, z, w});
                            }
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
        --w1;
        ++w2;
        active_coords_4d = tmp;
    }

    cout << active_coords_4d.size() << '\n';
}

int main() {
    part1();
    part2();
    return 0;
}