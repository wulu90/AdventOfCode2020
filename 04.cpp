#include <iostream>
#include <fstream>
#include <string_view>
#include <vector>
#include <string>
#include <ranges>

using namespace std;

enum class field : u_int8_t
{
    byr = 0b00000001,
    iyr = 0b00000010,
    eyr = 0b00000100, // 1 << 2,
    hgt = 0b00001000, // 1 << 3,
    hcl = 0b00010000, // 1 << 4,
    ecl = 0b00100000, // 1 << 5,
    pid = 0b01000000, // 1 << 6,
    cid = 0b10000000, // 1 << 7
};

void part1()
{
    ifstream input("input");
    string line;

    u_int8_t passport = 0;
    int validcount = 0;
    while (input.good())
    {
        getline(input, line);
        if (line.empty() || input.eof())
        {
            if (passport == 0b11111111 || passport == 0b01111111)
            {
                ++validcount;
            }
            passport = 0;
        }
        else
        {
            string_view sv{line};
            for (auto sub_sv : sv | ranges::views::split(" "sv))
            {
                auto sp_v = string_view{sub_sv} | ranges::views::split(":"sv);
                string_view fname{*sp_v.begin()};

                if (fname == "byr"sv)
                {
                    passport |= static_cast<underlying_type_t<field>>(field::byr);
                }
                else if (fname == "iyr"sv)
                {
                    passport |= static_cast<underlying_type_t<field>>(field::iyr);
                }
                else if (fname == "eyr"sv)
                {
                    passport |= static_cast<underlying_type_t<field>>(field::eyr);
                }
                else if (fname == "hgt"sv)
                {
                    passport |= static_cast<underlying_type_t<field>>(field::hgt);
                }
                else if (fname == "hcl"sv)
                {
                    passport |= static_cast<underlying_type_t<field>>(field::hcl);
                }
                else if (fname == "ecl"sv)
                {
                    passport |= static_cast<underlying_type_t<field>>(field::ecl);
                }
                else if (fname == "pid"sv)
                {
                    passport |= static_cast<underlying_type_t<field>>(field::pid);
                }
                else if (fname == "cid"sv)
                {
                    passport |= static_cast<underlying_type_t<field>>(field::cid);
                }
            }
        }
    }

    cout << validcount << '\n';
}

int main()
{
    part1();
    return 0;
}