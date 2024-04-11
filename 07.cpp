#include <charconv>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <ranges>
#include <set>
#include <string>
#include <string_view>
#include <vector>
using namespace std;

void part1() {
    ifstream input("input");
    string line;
    map<string, vector<string>> bag_partents;
    while (getline(input, line)) {
        auto split_sv = line | ranges::views::split(" contain "sv);
        string_view pbag_sv{split_sv.front()};                                      // light red bags
        string pbag_name{pbag_sv.data(), pbag_sv.data() + pbag_sv.length() - 5};    // 5 -> " bags";

        string_view cbags_sv{*++split_sv.begin()};
        // auto cbags_spsv=cbags_sv|ranges::views::split(", "sv);
        for (auto cbags_subr : cbags_sv | ranges::views::split(", "sv)) {
            string_view cbag_sv{cbags_subr};
            auto sp1 = cbag_sv.find_first_of(' ');
            auto sp2 = cbag_sv.find_last_of(' ');
            string cname{cbag_sv.substr(sp1 + 1, sp2 - sp1 - 1)};

            bag_partents[cname].push_back(pbag_name);
        }
    }

    queue<string> q;
    q.push("shiny gold"s);
    set<string> visited;

    while (!q.empty()) {
        auto n = q.size();
        for (size_t i = 0; i < n; ++i) {
            visited.insert(q.front());

            for (auto s : bag_partents[q.front()]) {
                if (!visited.contains(s)) {
                    q.push(s);
                }
            }
            q.pop();
        }
    }

    cout << visited.size() - 1 << '\n';
}

void part2() {
    ifstream input("input");
    string line;
    // map<string, vector<string>> bag_partents;
    map<string, vector<pair<string, int>>> bag_tree;
    while (getline(input, line)) {
        auto split_sv = line | ranges::views::split(" contain "sv);
        string_view pbag_sv{split_sv.front()};                                      // light red bags
        string pbag_name{pbag_sv.data(), pbag_sv.data() + pbag_sv.length() - 5};    // 5 -> " bags";

        string_view cbags_sv{*++split_sv.begin()};
        // auto cbags_spsv=cbags_sv|ranges::views::split(", "sv);
        for (auto cbags_subr : cbags_sv | ranges::views::split(", "sv)) {
            string_view cbag_sv{cbags_subr};
            auto sp1 = cbag_sv.find_first_of(' ');
            auto sp2 = cbag_sv.find_last_of(' ');
            string cname{cbag_sv.substr(sp1 + 1, sp2 - sp1 - 1)};
            int cbag_num;
            from_chars(cbag_sv.data(), cbag_sv.data() + sp1, cbag_num);
            bag_tree[pbag_name].push_back({cname, cbag_num});
            // bag_partents[cname].push_back(pbag_name);
        }
    }

    int64_t bagscount = 0;

    queue<pair<string, int>> q;
    for (auto [str, n] : bag_tree["shiny gold"s]) {
        q.push({str, n});
    }

    while (!q.empty()) {
        auto num = q.size();
        for (size_t i = 0; i < num; ++i) {
            auto [str, n] = q.front();
            bagscount += n;
            for (auto [cname, cnum] : bag_tree[str]) {
                if (cname != "other"s) {
                    q.push({cname, cnum * n});
                }
            }
            q.pop();
        }
    }
    cout << bagscount << '\n';
}

int main() {
    part1();
    part2();
    return 0;
}