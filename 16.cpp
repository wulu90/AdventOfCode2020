#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>
using namespace std;

// struct filter {
//     int x1;
//     int y1;
//     int x2;
//     int y2;
// };

vector<int> parse_int(const string& str) {
    vector<int> v;
    regex pa{R"(\d+)"};
    for (sregex_iterator p(str.begin(), str.end(), pa); p != sregex_iterator{}; ++p) {
        v.push_back(stoi(p->str()));
    }
    return v;
}

bool valid(const vector<vector<int>> filter, int n) {
    bool re = false;

    for (auto vec : filter) {
        if ((n >= vec[0] && n <= vec[1]) || (n >= vec[2] && n <= vec[3])) {
            re = true;
            break;
        }
    }
    return re;
}

void part1() {
    ifstream input("input");
    int empty_line_count = 0;

    vector<vector<int>> filter;
    vector<vector<int>> nearby_tickets;
    vector<int> your_ticket;
    for (string line; getline(input, line);) {
        if (line.empty()) {
            ++empty_line_count;
            getline(input, line);    // skip your ticket: or nearby tickets:
            continue;
        }

        if (empty_line_count == 0) {
            filter.push_back(parse_int(line));
        } else if (empty_line_count == 1) {
            your_ticket = parse_int(line);
        } else {
            nearby_tickets.push_back(parse_int(line));
        }
    }

    int err = 0;

    for (auto ticket : nearby_tickets) {
        for (auto field : ticket) {
            if (!valid(filter, field)) {
                err += field;
            }
        }
    }

    cout << err << '\n';
}

int main() {
    part1();
    return 0;
}