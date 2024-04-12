#include <array>
#include <charconv>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

void bitmask(u_int64_t& n, const array<int, 36>& mask) {
    for (size_t i = 0; i < 36; ++i) {
        if (mask[i] == 1) {
            n = n | (1ull << (35 - i));
        } else if (mask[i] == 0) {
            n = n & (~(1ull << (35 - i)));
        }
    }
}

array<int, 36> parse_mask(const string& str) {
    array<int, 36> mask;

    // mask = 11110X1XXX11001X01X00011001X00X00000

    for (size_t i = 0; i < 36; ++i) {
        mask[i] = str[i + 7] - '0';
    }
    return mask;
}

pair<int, u_int64_t> parse_address_value(const string& str) {
    // mem[28496] = 122879146

    auto left_square_brackets  = str.find('[');
    auto right_square_brackets = str.find(']');

    int address = 0;
    from_chars(str.data() + left_square_brackets + 1, str.data() + right_square_brackets, address);

    auto rspace     = str.find_last_of(' ');
    u_int64_t value = 0;
    from_chars(str.data() + rspace + 1, str.data() + str.length(), value);

    return {address, value};
}

void part1() {
    ifstream input("input");
    string line;

    map<int, u_int64_t> addr_value;
    array<int, 36> mask;
    while (getline(input, line)) {
        if (line.starts_with("mask")) {
            mask = parse_mask(line);
        } else {
            auto [a, v] = parse_address_value(line);
            bitmask(v, mask);
            addr_value[a] = v;
        }
    }

    u_int64_t num = 0;
    for (auto [a, v] : addr_value) {
        num += v;
    }

    cout << num << '\n';
}

int main() {
    part1();
    return 0;
}