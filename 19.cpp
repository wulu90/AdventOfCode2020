#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <ranges>
#include <regex>
#include <set>
#include <string>
#include <string_view>
#include <vector>
using namespace std;

struct rules {
    int no;
    vector<vector<int>> subs;
};

pair<int, vector<vector<int>>> parse_rule(const string& str) {
    vector<vector<int>> subrulevec;

    regex pa{R"(\d+)"};
    smatch ma;
    regex_search(str, ma, pa);
    int no = stoi(ma[0]);

    auto comma = str.find(':');
    string_view sv{str.begin() + comma + 1, str.end()};
    for (auto spilt : sv | ranges::views::split("|"sv)) {
        string_view subsv{spilt};
        vector<int> subrule;
        for (regex_iterator<string_view::const_iterator> p{subsv.begin(), subsv.end(), pa};
             p != regex_iterator<string_view::const_iterator>{}; ++p) {
            subrule.push_back(stoi(p->str()));
        }
        subrulevec.push_back(subrule);
    }

    return {no, subrulevec};
}

vector<int> find_rules_only_include_given(const map<int, vector<vector<int>>>& rulemap, const set<int>& replace_seed) {
    vector<int> re;
    for (auto& [rule_no, sub_rules_vec] : rulemap) {
        bool onlyhave = true;
        if (!replace_seed.contains(rule_no)) {
            for (auto& sub_rule : sub_rules_vec) {
                for (auto child_no : sub_rule) {
                    if (!replace_seed.contains(child_no)) {
                        onlyhave = false;
                        break;
                    }
                }
                if (!onlyhave) {
                    break;
                }
            }
        }
        if (onlyhave) {
            re.push_back(rule_no);
        }
    }
    return re;
}

void replace_with_child_no(map<int, vector<vector<int>>>& rulemap, const vector<int>& tobe_replace, const set<int>& leaf_nos) {
    for (auto tbr : tobe_replace) {
        vector<vector<int>> finallyvec;

        for (auto& sub_rules_vec : rulemap[tbr]) {
            vector<vector<int>> rpvec;    // replaced vec

            if (!leaf_nos.contains(sub_rules_vec[0])) {
                for (auto rp_sub_rules_vec : rulemap[sub_rules_vec[0]]) {
                    rpvec.push_back(rp_sub_rules_vec);
                }
            } else {
                vector<int> tv{sub_rules_vec[0]};
                rpvec.push_back(tv);
            }

            for (size_t i = 1; i < sub_rules_vec.size(); ++i) {
                if (leaf_nos.contains(sub_rules_vec[i])) {
                    for (auto& v : rpvec) {
                        v.push_back(sub_rules_vec[i]);
                    }
                } else {
                    vector<vector<int>> tmpvecvec;
                    for (const auto& rp_sub_rules_vec : rulemap[sub_rules_vec[i]]) {
                        for (const auto& v : rpvec) {
                            vector<int> tmpvec;
                            copy(v.begin(), v.end(), back_inserter(tmpvec));
                            copy(rp_sub_rules_vec.begin(), rp_sub_rules_vec.end(), back_inserter(tmpvec));
                            tmpvecvec.push_back(tmpvec);
                        }
                    }
                    rpvec = tmpvecvec;
                }
            }

            copy(rpvec.begin(), rpvec.end(), back_inserter(finallyvec));
        }

        rulemap[tbr] = finallyvec;
    }
}

set<string> rule_to_str(const vector<vector<int>>& rule, const map<int, string>& strrules) {
    set<string> re;
    for (auto& v : rule) {
        string str;
        str.reserve(v.size());
        for (auto i : v) {
            str.append(strrules.at(i));
        }
        re.insert(str);
    }

    return re;
}

void solve() {
    ifstream input("input");
    map<int, vector<vector<int>>> rulemap;
    map<int, vector<int>> parentmap;
    map<int, string> strrules;
    vector<string> msgvec;

    string line;
    while (getline(input, line) && !line.empty()) {
        if (line.contains('"')) {
            auto ql = line.find('"');
            auto qr = line.find_last_of('"');
            auto co = line.find(':');
            strrules.insert({stoi(line.substr(0, co)), line.substr(ql + 1, qr - ql - 1)});

        } else {
            auto p = parse_rule(line);
            rulemap.insert(p);

            for (auto vec : p.second) {
                for (auto r : vec) {
                    parentmap[r].push_back(p.first);
                }
            }
        }
    }

    while (getline(input, line)) {
        msgvec.push_back(line);
    }

    set<int> leaf_nos;
    for (auto [no, _] : strrules) {
        leaf_nos.insert(no);
    }

    auto leaf_1 = find_rules_only_include_given(rulemap, leaf_nos);    // find only have 'a' b', and not need replace

    set<int> replace_seed;
    for (auto no : leaf_nos) {
        replace_seed.insert(no);
    }
    for (auto no : leaf_1) {
        replace_seed.insert(no);
    }

    auto toberplaced = find_rules_only_include_given(rulemap, replace_seed);

    while (replace_seed.size() != rulemap.size() + strrules.size()) {
        replace_with_child_no(rulemap, toberplaced, leaf_nos);
        for (auto no : toberplaced) {
            replace_seed.insert(no);
        }
        toberplaced = find_rules_only_include_given(rulemap, replace_seed);
    }

    auto rule_0    = rule_to_str(rulemap[0], strrules);
    int validcount = 0;

    for (auto& msg : msgvec) {
        if (rule_0.contains(msg)) {
            ++validcount;
        }
    }

    cout << validcount << '\n';

    auto set_31 = rule_to_str(rulemap[31], strrules);
    auto set_42 = rule_to_str(rulemap[42], strrules);

    /**
    ofstream ouput("output.txt");

    for (auto& s : set_31) {
        ouput << s << '\n';
    }
    ouput << '\n';

    for (auto& s : set_42) {
        ouput << s << '\n';
    }
    ouput << '\n';
    */

    int validcount_2 = 0;
    int len          = 8;    // in 42 and 31   all rule string's lenggth is 8
    for (const auto& msg : msgvec) {
        if (msg.length() % len != 0) {
            continue;
        }

        bool substr_in_31   = false;
        bool substr_in_42   = false;
        bool order_correct  = true;
        int substr_42_count = 0;
        int substr_31_count = 0;
        for (size_t i = 0; i < msg.length() / len; ++i) {
            string substr = msg.substr(i * len, len);
            if (set_31.contains(substr)) {
                substr_in_31 = true;
                ++substr_31_count;
                if (!substr_in_42) {
                    order_correct = false;
                    break;
                }
            }
            if (set_42.contains(substr)) {
                substr_in_42 = true;
                ++substr_42_count;
                if (substr_in_31) {
                    order_correct = false;
                    break;
                }
            }
        }

        if (substr_in_42 && substr_in_31 && order_correct && substr_42_count > substr_31_count) {
            ++validcount_2;

            /**
            ouput << msg << '\n';
            ouput << msg.length() / len << ": "s;

            for (size_t i = 0; i < msg.length() / len; ++i) {
                string substr = msg.substr(i * len, len);
                if (set_31.contains(substr)) {
                    ouput << 31 << ' ';
                }
                if (set_42.contains(substr)) {
                    ouput << 42 << ' ';
                }
            }
            ouput << '\n';
            */
        }
    }
    cout << validcount_2 << '\n';
}

int main() {
    solve();
    return 0;
}