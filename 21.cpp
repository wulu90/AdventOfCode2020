#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <ranges>
#include <set>
#include <string>
#include <string_view>
#include <vector>
using namespace std;

struct food {
    set<string> ingredients;
    set<string> allergens;

    food(const string& str) {
        auto left_parenthesis = str.find('(');
        for (auto sub_sv : string_view(str.data(), left_parenthesis - 1) | ranges::views::split(" "sv)) {
            ingredients.emplace(string_view{sub_sv});
        }

        for (auto sub_sv : string_view{str.begin() + left_parenthesis + 10, str.end() - 1} | ranges::views::split(", "sv)) {
            allergens.emplace(string_view{sub_sv});
        }
    }
};

vector<food> read_input() {
    ifstream input("input");
    vector<food> re;

    for (string line; getline(input, line);) {
        re.push_back(line);
    }
    return re;
}

void solve() {
    vector<food> food_vec = read_input();
    map<string, set<string>> all_ing;
    map<string, int> ing_count;
    for (auto& f : food_vec) {
        for (auto& a : f.allergens) {
            if (all_ing.contains(a)) {
                set<string> tmpset;
                set_intersection(all_ing[a].begin(), all_ing[a].end(), f.ingredients.begin(), f.ingredients.end(),
                                 inserter(tmpset, tmpset.end()));
                all_ing[a] = tmpset;
            } else {
                all_ing[a] = f.ingredients;
            }
        }

        for (auto& i : f.ingredients) {
            ++ing_count[i];
        }
    }

    set<string> simpled;
    while (simpled.size() != all_ing.size()) {
        for (auto& [all, ings] : all_ing) {
            if (ings.size() == 1) {
                simpled.insert(*ings.begin());
            } else {
                for (auto& s : simpled) {
                    ings.erase(s);
                }
            }
        }
    }

    int re = 0;
    for (auto& [i, c] : ing_count) {
        if (!simpled.contains(i)) {
            re += c;
        }
    }

    cout << re << '\n';

    for (auto& [a, i] : all_ing) {
        cout << *i.begin() << ',';
    }

    cout << '\n';
}

int main() {
    solve();
    return 0;
}