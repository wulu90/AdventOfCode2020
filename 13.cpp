#include <algorithm>
#include <charconv>
#include <fstream>
#include <iostream>
#include <map>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>
using namespace std;

void part1() {
    ifstream input("input");
    int earliest = 0;
    input >> earliest;
    input.get();
    vector<int> busid_vec;
    string line;
    getline(input, line);
    auto id_sv = line | ranges::views::split(","sv);
    for (auto sub : id_sv) {
        string_view sv{sub};
        if (!sv.starts_with('x')) {
            int id = 0;
            from_chars(sv.begin(), sv.end(), id);
            busid_vec.push_back(id);
        }
    }

    vector<int> wait_vec(busid_vec.size(), 0);
    for (size_t i = 0; i < busid_vec.size(); ++i) {
        wait_vec[i] = (earliest / busid_vec[i] + 1) * busid_vec[i] - earliest;
    }

    auto mine = min_element(wait_vec.begin(), wait_vec.end());
    cout << *mine * busid_vec[mine - wait_vec.begin()] << '\n';
}

void exgcd(int64_t a, int64_t b, int64_t& x, int64_t& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return;
    }
    exgcd(b, a % b, y, x);
    y -= a / b * x;
}

// https://oi-wiki.org/math/number-theory/crt/
int64_t crt(vector<int64_t> va, vector<int64_t> vr) {
    int64_t n   = 1;
    int64_t ans = 0;
    for (size_t i = 0; i < va.size(); ++i) {
        n = n * vr[i];
    }

    for (size_t i = 0; i < va.size(); ++i) {
        int64_t m = n / vr[i];
        int64_t b, y;
        exgcd(m, vr[i], b, y);
        ans = (ans + va[i] * m * b % n) % n;
    }

    return (ans % n + n) % n;
}

void part2() {
    ifstream input("input");
    string line;
    getline(input, line);
    getline(input, line);
    map<int, int> id_offset;
    auto id_split = line | ranges::views::split(","sv);
    int offset    = 0;
    int id        = 0;
    for (auto sub : id_split) {
        string_view sv{sub};
        if (!sv.starts_with('x')) {
            from_chars(sv.begin(), sv.end(), id);
            id_offset.insert({id, offset});
        }
        ++offset;
    }

    vector<int64_t> id_vec;
    vector<int64_t> remain_vec;
    for (auto [id, of] : id_offset) {
        id_vec.push_back(id);
        remain_vec.push_back(of == 0 ? 0 : id - of);
    }

    // chinese remainder theorem
    cout << crt(remain_vec, id_vec) << '\n';
}

int main() {
    part1();
    part2();
    return 0;
}