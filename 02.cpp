#include <algorithm>
#include <charconv>
#include <fstream>
#include <iostream>
#include <ranges>
#include <string>
#include <string_view>

using namespace std;

struct pass {
    int lowest;
    int highest;
    char letter;
    string str;
    bool valid;

    pass(const string& s) : valid{false} {
        auto inx = s.find('-');
        from_chars(&s[0], &s[inx], lowest);
        auto sp = s.find(' ');
        from_chars(&s[inx + 1], &s[sp], highest);

        letter = s[sp + 1];
        str    = s.substr(sp + 4);

        auto n = count(str.begin(), str.end(), letter);
        if (n >= lowest && n <= highest) {
            valid = true;
        }
    }

    bool valid2() {
        if ((str[lowest - 1] == letter && str[highest - 1] != letter) || (str[lowest - 1] != letter && str[highest - 1] == letter)) {
            return true;
        }
        return false;
    }
};

void part1() {
    ifstream input("input");
    string line;
    int count = 0;
    while (getline(input, line)) {
        pass p(line);
        if (p.valid) {
            ++count;
        }
    }

    cout << count << '\n';
}

void part2() {
    ifstream input("input");
    string line;
    int count = 0;
    while (getline(input, line)) {
        pass p(line);
        if (p.valid2()) {
            ++count;
        }
    }

    cout << count << '\n';
}

int main() {
    part1();
    part2();
}
