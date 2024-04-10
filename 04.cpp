#include <algorithm>
#include <charconv>
#include <fstream>
#include <iostream>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

enum class field : u_int8_t {
    byr = 0b00000001,
    iyr = 0b00000010,
    eyr = 0b00000100,    // 1 << 2,
    hgt = 0b00001000,    // 1 << 3,
    hcl = 0b00010000,    // 1 << 4,
    ecl = 0b00100000,    // 1 << 5,
    pid = 0b01000000,    // 1 << 6,
    cid = 0b10000000,    // 1 << 7
};

void part1() {
    ifstream input("input");
    string line;

    u_int8_t passport = 0;
    int validcount    = 0;
    while (input.good()) {
        getline(input, line);
        if (line.empty() || input.eof()) {
            if (passport == 0b11111111 || passport == 0b01111111) {
                ++validcount;
            }
            passport = 0;
        } else {
            string_view sv{line};
            for (auto sub_sv : sv | ranges::views::split(" "sv)) {
                auto sp_v = string_view{sub_sv} | ranges::views::split(":"sv);
                string_view fname{*sp_v.begin()};

                if (fname == "byr"sv) {
                    passport |= static_cast<underlying_type_t<field>>(field::byr);
                } else if (fname == "iyr"sv) {
                    passport |= static_cast<underlying_type_t<field>>(field::iyr);
                } else if (fname == "eyr"sv) {
                    passport |= static_cast<underlying_type_t<field>>(field::eyr);
                } else if (fname == "hgt"sv) {
                    passport |= static_cast<underlying_type_t<field>>(field::hgt);
                } else if (fname == "hcl"sv) {
                    passport |= static_cast<underlying_type_t<field>>(field::hcl);
                } else if (fname == "ecl"sv) {
                    passport |= static_cast<underlying_type_t<field>>(field::ecl);
                } else if (fname == "pid"sv) {
                    passport |= static_cast<underlying_type_t<field>>(field::pid);
                } else if (fname == "cid"sv) {
                    passport |= static_cast<underlying_type_t<field>>(field::cid);
                }
            }
        }
    }

    cout << validcount << '\n';
}

bool check_birth_year(const string_view& sv) {
    if (sv.length() != 4) {
        return false;
    }

    int year = 0;
    from_chars(sv.data(), sv.data() + sv.size(), year);
    if (year >= 1920 && year <= 2002) {
        return true;
    }
    return false;
}

bool check_issue_year(const string_view& sv) {
    if (sv.length() != 4) {
        return false;
    }

    int year = 0;
    from_chars(sv.data(), sv.data() + sv.size(), year);
    if (year >= 2010 && year <= 2020) {
        return true;
    }
    return false;
}

bool check_expiration_year(const string_view& sv) {
    if (sv.length() != 4) {
        return false;
    }

    int year = 0;
    from_chars(sv.data(), sv.data() + sv.size(), year);
    if (year >= 2020 && year <= 2030) {
        return true;
    }
    return false;
}

bool check_height(const string_view& sv) {
    auto len = sv.length();
    string_view unit_sv{sv.data() + len - 2, sv.data() + len};
    if (!(unit_sv == "cm"sv || unit_sv == "in"sv)) {
        return false;
    }

    int hgt = 0;
    from_chars(sv.data(), sv.data() + len - 2, hgt);

    if ((unit_sv == "cm"sv && (hgt >= 150 && hgt <= 193)) || (unit_sv == "in"sv && (hgt >= 59 && hgt <= 76))) {
        return true;
    }
    return false;
}

bool check_hair_color(const string_view& sv) {
    if (sv[0] != '#') {
        return false;
    }
    if (sv.length() != 7) {
        return false;
    }

    bool hexcheck = false;
    for (int i = 1; i <= 6; ++i) {
        if ((sv[i] >= '0' && sv[i] <= '9') || (sv[i] >= 'a' && sv[i] <= 'f')) {
            hexcheck = true;
        } else {
            hexcheck = false;
        }
    }
    return hexcheck;
}

bool check_eye_color(const string_view& sv) {
    static vector<string> eye_color_vec{"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
    auto f = find(eye_color_vec.begin(), eye_color_vec.end(), sv);
    if (f == eye_color_vec.end()) {
        return false;
    }
    return true;
}

bool check_passport_id(const string_view& sv) {
    if (sv.length() != 9) {
        return false;
    }

    bool digit = false;
    for (int i = 0; i < 9; ++i) {
        if (isdigit(sv[i])) {
            digit = true;
        } else {
            digit = false;
        }
    }
    return digit;
}

void part2() {
    ifstream input("input");
    string line;

    u_int8_t passport = 0;
    int validcount    = 0;
    while (input.good()) {
        getline(input, line);
        if (line.empty() || input.eof()) {
            if (passport == 0b11111111 || passport == 0b01111111) {
                ++validcount;
            }
            passport = 0;
        } else {
            string_view sv{line};
            for (auto sub_sv : sv | ranges::views::split(" "sv)) {
                auto sp_v = string_view{sub_sv} | ranges::views::split(":"sv);
                string_view fname{*sp_v.begin()};
                string_view fvalue{*++sp_v.begin()};
                if (fname == "byr"sv) {
                    if (check_birth_year(fvalue)) {
                        passport |= static_cast<underlying_type_t<field>>(field::byr);
                    }
                } else if (fname == "iyr"sv) {
                    if (check_issue_year(fvalue)) {
                        passport |= static_cast<underlying_type_t<field>>(field::iyr);
                    }
                } else if (fname == "eyr"sv) {
                    if (check_expiration_year(fvalue)) {
                        passport |= static_cast<underlying_type_t<field>>(field::eyr);
                    }
                } else if (fname == "hgt"sv) {
                    if (check_height(fvalue)) {
                        passport |= static_cast<underlying_type_t<field>>(field::hgt);
                    }
                } else if (fname == "hcl"sv) {
                    if (check_hair_color(fvalue)) {
                        passport |= static_cast<underlying_type_t<field>>(field::hcl);
                    }
                } else if (fname == "ecl"sv) {
                    if (check_eye_color(fvalue)) {
                        passport |= static_cast<underlying_type_t<field>>(field::ecl);
                    }
                } else if (fname == "pid"sv) {
                    if (check_passport_id(fvalue)) {
                        passport |= static_cast<underlying_type_t<field>>(field::pid);
                    }
                } else if (fname == "cid"sv) {
                    passport |= static_cast<underlying_type_t<field>>(field::cid);
                }
            }
        }
    }

    cout << validcount << '\n';
}

int main() {
    part1();
    part2();
    return 0;
}