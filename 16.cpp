#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <set>
#include <string>
#include <vector>
using namespace std;

vector<int> parse_int(const string& str) {
    vector<int> v;
    regex pa{R"(\d+)"};
    for (sregex_iterator p(str.begin(), str.end(), pa); p != sregex_iterator{}; ++p) {
        v.push_back(stoi(p->str()));
    }
    return v;
}

bool valid(const vector<vector<int>> rules, int n) {
    bool re = false;

    for (auto vec : rules) {
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
        for (auto field_v : ticket) {
            if (!valid(filter, field_v)) {
                err += field_v;
            }
        }
    }

    cout << err << '\n';
}

// check value is valid in one field
bool value_valid_field(const vector<int>& vec, int n) {
    if ((n >= vec[0] && n <= vec[1]) || (n >= vec[2] && n <= vec[3])) {
        return true;
    } else {
        return false;
    }
}

void part2() {
    ifstream input("input");
    int empty_line_count = 0;

    size_t fields_num = 0;
    vector<vector<int>> rules;    // fields valid ranges
    vector<vector<int>> nearby_tickets;
    vector<int> your_ticket;
    vector<int> departure_indexvec;
    for (string line; getline(input, line);) {
        if (line.empty()) {
            ++empty_line_count;
            getline(input, line);    // skip your ticket: or nearby tickets:
            continue;
        }

        if (empty_line_count == 0) {
            rules.push_back(parse_int(line));
            if (line.starts_with("departure")) {
                departure_indexvec.push_back(fields_num);
            }
            ++fields_num;

        } else if (empty_line_count == 1) {
            your_ticket = parse_int(line);
        } else {
            nearby_tickets.push_back(parse_int(line));
        }
    }

    set<int> invalid_tis;
    for (size_t i = 0; i < nearby_tickets.size(); ++i) {
        for (auto field_v : nearby_tickets[i]) {
            if (!valid(rules, field_v)) {
                invalid_tis.insert(i);
            }
        }
    }

    set<int> valid_field_inx_set;
    for (size_t i = 0; i < fields_num; ++i) {
        valid_field_inx_set.insert(i);
    }

    vector<set<int>> valid_field_inx_setvec(rules.size(), valid_field_inx_set);

    for (size_t i = 0; i < nearby_tickets.size(); ++i) {
        if (invalid_tis.contains(i))
            continue;

        for (size_t j = 0; j < fields_num; ++j) {
            for (size_t k = 0; k < fields_num; ++k) {
                if (!valid_field_inx_setvec[j].contains(k))
                    continue;

                if (!value_valid_field(rules[k], nearby_tickets[i][j])) {
                    valid_field_inx_setvec[j].erase(k);
                }
            }
        }
    }

    // if no one is only one valid field??
    while (true) {
        if (all_of(valid_field_inx_setvec.begin(), valid_field_inx_setvec.end(), [](auto it) { return it.size() == 1; })) {
            break;
        }

        vector<int> remove_inx;
        for (auto& vset : valid_field_inx_setvec) {
            if (vset.size() == 1) {
                remove_inx.push_back(*vset.begin());
            }
        }

        for (auto& vset : valid_field_inx_setvec) {
            if (vset.size() != 1) {
                for (auto ri : remove_inx) {
                    vset.erase(ri);
                }
            }
        }
    }

    // departure
    vector<int> dvec;
    for (size_t i = 0; i < fields_num; ++i) {
        if (find(departure_indexvec.begin(), departure_indexvec.end(), *valid_field_inx_setvec[i].begin()) != departure_indexvec.end()) {
            dvec.push_back(i);
        }
    }

    int64_t re = 1;
    for (auto i : dvec) {
        re *= your_ticket[i];
    }

    cout << re << '\n';
}

int main() {
    part1();
    part2();
    return 0;
}