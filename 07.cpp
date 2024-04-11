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

int main() {
    part1();
    return 0;
}