#include <algorithm>
#include <array>
#include <charconv>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

u_int16_t str_bit(const string& str) {
    u_int16_t n = 0;
    int len     = str.size();
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == '#') {
            n |= (1u << (len - 1 - i));
        }
    }
    return n;
}

u_int16_t str_r_bit(const string& str) {
    u_int16_t n = 0;
    // int len     = str.size();
    for (size_t i = str.size() - 1; i < str.size(); --i) {
        if (str[i] == '#') {
            n |= (1u << i);
        }
    }
    return n;
}

struct tile {
    int id;
    vector<string> img;
    array<u_int16_t, 8> borders_bit_arr;    // top top_r,right,right_r,bottom,bottom_r,left,left_r

    vector<int> adj_ids;           // adjacent ids
    set<u_int16_t> common_bits;    // border with adjacent tile
    vector<string> orienimg;       // rotate,flip

    void border_bit() {
        string left_str, right_str;
        for (auto& s : img) {
            left_str.push_back(s.front());
            right_str.push_back(s.back());
        }
        borders_bit_arr[0] = str_bit(img.front());
        borders_bit_arr[1] = str_r_bit(img.front());
        borders_bit_arr[2] = str_bit(right_str);
        borders_bit_arr[3] = str_r_bit(right_str);
        borders_bit_arr[4] = str_bit(img.back());
        borders_bit_arr[5] = str_r_bit(img.back());
        borders_bit_arr[6] = str_bit(left_str);
        borders_bit_arr[7] = str_r_bit(left_str);
    }

    /**
    u_int16_t top_bit;
    u_int16_t top_r_bit;
    u_int16_t right_bit;
    u_int16_t right_r_bit;
    u_int16_t bottom_bit;
    u_int16_t bottom_r_bit;
    u_int16_t left_bit;
    u_int16_t left_r_bit;

    void border_bit() {
        top_bit      = str_bit(img.front());
        top_r_bit    = str_r_bit(img.front());
        bottom_bit   = str_bit(img.back());
        bottom_r_bit = str_r_bit(img.back());

        string left_str, right_str;
        for (auto& s : img) {
            left_str.push_back(s.front());
            right_str.push_back(s.back());
        }
        left_bit    = str_bit(left_str);
        left_r_bit  = str_r_bit(left_str);
        right_bit   = str_bit(right_str);
        right_r_bit = str_r_bit(right_str);
    }
    */
};

bool is_adjacent(const tile& tile_l, const tile& tile_r) {
    for (auto border_bit : tile_l.borders_bit_arr) {
        if (find(tile_r.borders_bit_arr.begin(), tile_r.borders_bit_arr.end(), border_bit) != tile_r.borders_bit_arr.end()) {
            return true;
        }
    }
    return false;
}

vector<int> calc_tile_adjs(const vector<tile>& tiles_vec) {
    vector<int> adjs_numvec(tiles_vec.size(), 0);
    for (size_t i = 0; i < tiles_vec.size(); ++i) {
        for (size_t j = 0; j < tiles_vec.size(); ++j) {
            if (i != j && is_adjacent(tiles_vec[i], tiles_vec[j])) {
                ++adjs_numvec[i];
            }
        }
    }
    return adjs_numvec;
}

void read_input(vector<tile>& tiles_vec) {
    ifstream input("input");
    tile simg;
    string line;

    while (getline(input, line)) {
        if (line.empty()) {
            simg.border_bit();
            tiles_vec.push_back(simg);

        } else if (line.contains("Tile")) {
            simg = tile{};
            from_chars(line.data() + 5, line.data() + line.length() - 1, simg.id);

        } else {
            simg.img.push_back(line);
        }
    }
}

void part1() {
    vector<tile> tiles_vec;
    read_input(tiles_vec);

    vector<int> adj_count_vec = calc_tile_adjs(tiles_vec);

    int64_t corner_mul = 1;
    for (size_t i = 0; i < adj_count_vec.size(); ++i) {
        if (adj_count_vec[i] == 2) {
            corner_mul *= tiles_vec[i].id;
        }
    }

    cout << corner_mul << '\n';
}

// clockwise 90
vector<string> rotate(const vector<string>& img) {
    auto len = img.front().size();
    vector<string> re(len, string(img.size(), ' '));
    for (size_t i = img.size() - 1; i < img.size(); --i) {
        for (size_t j = 0; j < len; ++j) {
            re[j][len - 1 - i] = img[i][j];
        }
    }
    return re;
}

vector<string> flip(const vector<string>& img) {
    vector<string> re;
    reverse_copy(img.begin(), img.end(), back_inserter(re));
    return re;
}

vector<vector<string>> orientations(const vector<string>& img) {
    auto ti     = img;
    auto fliped = flip(img);
    vector<vector<string>> orientations;
    for (int i = 0; i < 4; ++i) {
        ti = rotate(ti);
        orientations.push_back(ti);
    }
    for (int i = 0; i < 4; ++i) {
        fliped = rotate(fliped);
        orientations.push_back(fliped);
    }
    return orientations;
}

void calc_adj(tile& l, tile& r) {
    // for (auto border_bit : l.borders_bit_arr) {
    for (size_t i = 0; i < l.borders_bit_arr.size(); ++i) {
        if (find(r.borders_bit_arr.begin(), r.borders_bit_arr.end(), l.borders_bit_arr[i]) != r.borders_bit_arr.end()) {
            l.adj_ids.push_back(r.id);
            l.common_bits.insert(l.borders_bit_arr[i]);
            l.common_bits.insert(l.borders_bit_arr[i + 1]);
            break;    // one tile only has one common border with another tile
        }
    }
}

/// void match(vector<int>& grid, int square_len, int gi, int gj, vector<tile>& tiles_vec) {}

void part2() {
    vector<tile> tiles_vec;
    read_input(tiles_vec);
    map<int, tile> tilesmap;
    for (size_t i = 0; i < tiles_vec.size(); ++i) {
        for (size_t j = 0; j < tiles_vec.size(); ++j) {
            if (i != j) {
                calc_adj(tiles_vec[i], tiles_vec[j]);
            }
        }
    }
    for (auto& t : tiles_vec) {
        tilesmap.insert({t.id, t});
    }

    auto it            = find_if(tiles_vec.begin(), tiles_vec.end(), [](tile t) { return t.adj_ids.size() == 2; });
    auto left_top_tile = *it;

    for (auto& ori : orientations(left_top_tile.img)) {
        string rightstr;
        for (auto& s : ori) {
            rightstr.push_back(s.back());
        }
        auto right_bit  = str_bit(rightstr);
        auto bottom_bit = str_bit(ori.back());

        if (left_top_tile.common_bits.contains(right_bit) && left_top_tile.common_bits.contains(bottom_bit)) {
            left_top_tile.orienimg = ori;
            break;
        }
    }

    string lt_right_str;
    for (auto& s : left_top_tile.orienimg) {
        lt_right_str.push_back(s.back());
    }
    string lt_bottom_str = left_top_tile.orienimg.back();

    size_t square_len = sqrt(tiles_vec.size());
    vector<vector<int>> grid(square_len, vector<int>(square_len, 0));
    grid[0][0] = left_top_tile.id;

    for (auto adj : left_top_tile.adj_ids) {
        for (auto& ori : orientations(tilesmap[adj].img)) {
            string adj_left_str;
            string adj_top_str = ori.front();
            for (auto& s : ori) {
                adj_left_str.push_back(s.front());
            }

            if (adj_left_str == lt_right_str) {
                grid[0][1] = adj;
            }

            if (adj_top_str == lt_bottom_str) {
                grid[1][0] = adj;
            }
        }
    }

    set<int> used{grid[0][0], grid[0][1], grid[1][0]};

    for (size_t i = 0; i < square_len; ++i) {
        for (size_t j = 0; j < square_len; ++j) {
            if (i + j == 0 || i + j == 1) {
                continue;
            }

            if (grid[i][j] != 0) {
                continue;
            }

            if (i == 0 || j == 0) {
                auto prev_id     = i == 0 ? grid[0][j - 1] : grid[i - 1][0];
                size_t adj_count = 3;
                if ((i == 0 && j == square_len - 1) || (i == square_len - 1 && j == 0)) {
                    adj_count = 2;
                }
                for (auto adj : tilesmap[prev_id].adj_ids) {
                    if (tilesmap[adj].adj_ids.size() == adj_count && !used.contains(adj)) {
                        grid[i][j] = adj;
                        used.insert(adj);
                        break;
                    }
                }
            } else {
                auto up_id   = grid[i - 1][j];
                auto left_id = grid[i][j - 1];

                for (auto adj : tilesmap[up_id].adj_ids) {
                    if (find(tilesmap[left_id].adj_ids.begin(), tilesmap[left_id].adj_ids.end(), adj) != tilesmap[left_id].adj_ids.end() &&
                        !used.contains(adj)) {
                        grid[i][j] = adj;
                        used.insert(adj);
                        break;
                    }
                }
            }
        }
    }

    tilesmap[left_top_tile.id].orienimg = left_top_tile.orienimg;

    for (size_t i = 0; i < square_len; ++i) {
        for (size_t j = 0; j < square_len; ++j) {
            if (i == 0 && j == 0) {
                continue;
            }

            string adj_right_str, adj_bottom_str;
            if (j > 0) {
                for (auto& s : tilesmap[grid[i][j - 1]].orienimg) {
                    adj_right_str.push_back(s.back());
                }
            }
            if (i > 0) {
                adj_bottom_str = tilesmap[grid[i - 1][j]].orienimg.back();
            }

            for (auto& orie : orientations(tilesmap[grid[i][j]].img)) {
                string left_str, top_str;

                for (auto& s : orie) {
                    left_str.push_back(s.front());
                }
                top_str = orie.front();

                if (i == 0) {
                    if (adj_right_str == left_str) {
                        tilesmap[grid[i][j]].orienimg = orie;
                        break;
                    }
                } else if (j == 0) {
                    if (adj_bottom_str == top_str) {
                        tilesmap[grid[i][j]].orienimg = orie;
                        break;
                    }
                } else {
                    if (adj_right_str == left_str && adj_bottom_str == top_str) {
                        tilesmap[grid[i][j]].orienimg = orie;
                        break;
                    }
                }
            }
        }
    }

    /**
    ofstream output("output_20.txt");

    for (size_t i = 0; i < square_len; ++i) {
        for (size_t k = 0; k < 10; ++k) {
            for (size_t j = 0; j < square_len; ++j) {
                output << tilesmap[grid[i][j]].orienimg[k] << ' ';
            }
            output << '\n';
        }
        output << '\n';
    }
    */

    auto actual_len = tiles_vec.front().img.size() - 2;
    vector<string> actual_img;
    for (size_t i = 0; i < square_len; ++i) {
        for (size_t k = 0; k < actual_len; ++k) {
            string str;
            for (size_t j = 0; j < square_len; ++j) {
                copy(tilesmap[grid[i][j]].orienimg[k + 1].begin() + 1, tilesmap[grid[i][j]].orienimg[k + 1].end() - 1, back_inserter(str));
            }
            actual_img.push_back(str);
        }
    }

    /**
    ofstream output("output_20_1.txt");
    for (auto& s : actual_img) {
        output << s << '\n';
    }
    */

    vector<string> seamonster{"                  # ", "#    ##    ##    ###", " #  #  #  #  #  #   "};
    vector<pair<size_t, size_t>> pattern;
    for (size_t i = 0; i < seamonster.size(); ++i) {
        for (size_t j = 0; j < seamonster.front().size(); ++j) {
            if (seamonster[i][j] == '#') {
                pattern.push_back({i, j});
            }
        }
    }

    int ans = 0;
    for (auto& ori : orientations(actual_img)) {
        vector<pair<size_t, size_t>> seamonster_indexs;
        for (size_t i = 0; i < ori.size(); ++i) {
            for (size_t j = 0; j < ori.front().size(); ++j) {
                bool is_seamonster = true;

                for (auto [a, b] : pattern) {
                    if (i + a >= ori.size() || j + b >= ori.front().size() || ori[i + a][j + b] != '#') {
                        is_seamonster = false;
                        break;
                    }
                }
                if (is_seamonster) {
                    seamonster_indexs.push_back({i, j});
                }
            }
        }

        if (seamonster_indexs.size() > 0) {
            auto finalimg = ori;
            for (auto [r, c] : seamonster_indexs) {
                for (auto [a, b] : pattern) {
                    finalimg[r + a][c + b] = 'O';
                }
            }
            for (auto& s : finalimg) {
                for (auto& c : s) {
                    if (c == '#') {
                        ++ans;
                    }
                }
            }
            break;
        }
    }

    cout << ans << '\n';
}

int main() {
    part1();
    part2();
    return 0;
}