#include <charconv>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum class direction { north, east, south, west };

struct instruction {
    char action;
    int value;

    instruction(const string& str) {
        action = str[0];
        from_chars(&str[1], str.data() + str.length(), value);
    }
};

void movef(char a, int v, int& x, int& y) {
    switch (a) {
    case 'N':
        y += v;
        break;
    case 'S':
        y -= v;
        break;
    case 'E':
        x += v;
        break;
    case 'W':
        x -= v;
        break;
    default:
        break;
    }
}

char conv_dir_action(direction curr) {
    static vector<char> dirs{'N', 'E', 'S', 'W'};
    size_t inx = static_cast<underlying_type_t<direction>>(curr);
    return dirs[inx];
}

direction turn(direction cur, char a, int v) {
    int i       = a == 'L' ? -v / 90 : v / 90;
    int dir_inx = (static_cast<underlying_type_t<direction>>(cur) + 4 + i) % 4;
    return direction{dir_inx};
}

void part1() {
    ifstream input("input");
    vector<instruction> ins_vec;
    for (string line; getline(input, line);) {
        ins_vec.emplace_back(line);
    }

    direction curr = direction::east;
    int x          = 0;
    int y          = 0;

    for (auto [a, v] : ins_vec) {
        switch (a) {
        case 'N':
        case 'S':
        case 'E':
        case 'W':
            movef(a, v, x, y);
            break;
        case 'F':
            movef(conv_dir_action(curr), v, x, y);
            break;
        case 'L':
        case 'R':
            curr = turn(curr, a, v);
            break;
        }
    }

    cout << abs(x) + abs(y) << '\n';
}

void rotate_waypoint(char a, int v, int& x, int& y) {
    int ox = x;
    int oy = y;
    if (a == 'L') {
        if (v == 90) {
            x = -oy;
            y = ox;
        } else if (v == 180) {
            x = -ox;
            y = -oy;
        } else {
            x = oy;
            y = -ox;
        }
    } else {
        if (v == 90) {
            x = oy;
            y = -ox;
        } else if (v == 180) {
            x = -ox;
            y = -oy;
        } else {
            x = -oy;
            y = ox;
        }
    }
}

void forward_waypoint(int v, int wx, int wy, int& x, int& y) {
    x += wx * v;
    y += wy * v;
}

void part2() {
    ifstream input("input");
    vector<instruction> ins_vec;
    for (string line; getline(input, line);) {
        ins_vec.emplace_back(line);
    }

    int x  = 0;
    int y  = 0;
    int wx = 10;
    int wy = 1;

    for (auto [a, v] : ins_vec) {
        switch (a) {
        case 'N':
        case 'S':
        case 'E':
        case 'W':
            movef(a, v, wx, wy);
            break;
        case 'L':
        case 'R':
            rotate_waypoint(a, v, wx, wy);
            break;
        case 'F':
            forward_waypoint(v, wx, wy, x, y);
            break;
        }
    }

    cout << abs(x) + abs(y) << '\n';
}

int main() {
    part1();
    part2();
    return 0;
}