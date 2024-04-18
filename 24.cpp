#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

struct hextile_coord {
    int r;
    int s;
    int q;
};

auto operator<=>(const hextile_coord& lhs, const hextile_coord& r) {
    return tie(lhs.r, lhs.s, lhs.q) <=> tie(r.r, r.s, r.q);
}

// https://www.redblobgames.com/grids/hexagons/#neighbors
hextile_coord neighbour(const string& str, const hextile_coord& hc) {
    static map<string, int> nei_str_inx{{"e", 0}, {"se", 1}, {"sw", 2}, {"w", 3}, {"nw", 4}, {"ne", 5}};
    static vector<vector<int>> nei_cood_off{{0, -1, 1}, {1, -1, 0}, {1, 0, -1}, {0, 1, -1}, {-1, 1, 0}, {-1, 0, 1}};

    return {hc.r + nei_cood_off[nei_str_inx[str]][0], hc.s + nei_cood_off[nei_str_inx[str]][1], hc.q + nei_cood_off[nei_str_inx[str]][2]};
}

vector<string> parse_steps(const string& str) {
    vector<string> ans;
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == 'e') {
            ans.push_back("e"s);
        } else if (str[i] == 'w') {
            ans.push_back("w"s);
        } else {    // s or n
            string s{str[i], str[i + 1]};
            ans.push_back(s);
            ++i;
        }
    }
    return ans;
}

vector<vector<string>> read_input() {
    ifstream input("input");
    vector<vector<string>> ans;

    for (string line; getline(input, line);) {
        ans.push_back(parse_steps(line));
    }
    return ans;
}

hextile_coord step_to_coord(const vector<string>& steps) {
    hextile_coord hextile{0, 0, 0};
    for (auto& str : steps) {
        hextile = neighbour(str, hextile);
    }
    return hextile;
}

void part1() {
    auto tilevec = read_input();

    map<hextile_coord, int> tile_flip_count;
    for (auto& steps : tilevec) {
        auto hextile = step_to_coord(steps);
        ++tile_flip_count[hextile];
    }

    int ans = 0;
    for (auto& [_, i] : tile_flip_count) {
        if (i % 2 != 0) {
            ++ans;
        }
    }

    cout << ans << '\n';
}

int main() {
    part1();
    return 0;
}