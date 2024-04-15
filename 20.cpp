#include <algorithm>
#include <array>
#include <charconv>
#include <fstream>
#include <iostream>
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

struct simage {
    int id;
    vector<string> img;
    array<u_int16_t, 8> border_bit_arr;    // top top_r,right,right_r,bottom,bottom_r,left,left_r

    void border_bit() {
        string left_str, right_str;
        for (auto& s : img) {
            left_str.push_back(s.front());
            right_str.push_back(s.back());
        }
        border_bit_arr[0] = str_bit(img.front());
        border_bit_arr[1] = str_r_bit(img.front());
        border_bit_arr[2] = str_bit(right_str);
        border_bit_arr[3] = str_r_bit(right_str);
        border_bit_arr[4] = str_bit(img.back());
        border_bit_arr[5] = str_r_bit(img.back());
        border_bit_arr[6] = str_bit(left_str);
        border_bit_arr[7] = str_r_bit(left_str);
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

bool is_adjacent(const simage& limg, const simage& rimg) {
    for (auto border_bit : limg.border_bit_arr) {
        if (find(rimg.border_bit_arr.begin(), rimg.border_bit_arr.end(), border_bit) != rimg.border_bit_arr.end()) {
            return true;
        }
    }
    return false;
}

void part1() {
    ifstream input("input");
    vector<simage> simg_vec;
    simage simg;

    string line;

    while (getline(input, line)) {
        if (line.empty()) {
            simg.border_bit();
            simg_vec.push_back(simg);

        } else if (line.contains("Tile")) {
            simg = simage{};
            from_chars(line.data() + 5, line.data() + line.length() - 1, simg.id);

        } else {
            simg.img.push_back(line);
        }
    }

    vector<int> adj_count_vec(simg_vec.size(), 0);
    for (size_t i = 0; i < simg_vec.size(); ++i) {
        for (size_t j = 0; j < simg_vec.size(); ++j) {
            if (i != j && is_adjacent(simg_vec[i], simg_vec[j])) {
                ++adj_count_vec[i];
            }
        }
    }

    int64_t corner_mul = 1;
    for (size_t i = 0; i < adj_count_vec.size(); ++i) {
        if (adj_count_vec[i] == 2) {
            corner_mul *= simg_vec[i].id;
        }
    }

    cout << corner_mul << '\n';
}

int main() {
    part1();
    return 0;
}