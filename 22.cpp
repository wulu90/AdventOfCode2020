#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
using namespace std;

void part1() {
    ifstream input("input");
    string line;
    vector<queue<int>> player_card;
    queue<int> q;
    while (input.good()) {
        getline(input, line);
        if (line.empty() || input.eof()) {
            player_card.push_back(q);
            q = queue<int>{};
        } else if (line.contains("Player")) {
            continue;
        } else {
            q.push(stoi(line));
        }
    }

    while (!(player_card[0].empty() || player_card[1].empty())) {
        auto i1 = player_card[0].front();
        player_card[0].pop();
        auto i2 = player_card[1].front();
        player_card[1].pop();

        if (i1 > i2) {
            player_card[0].push(i1);
            player_card[0].push(i2);
        } else {
            player_card[1].push(i2);
            player_card[1].push(i1);
        }
    }

    q = player_card[0].empty() ? player_card[1] : player_card[0];

    int re = 0;
    int n  = q.size();
    while (!q.empty()) {
        re += n * q.front();
        q.pop();
        --n;
    }

    cout << re << '\n';
}

queue<int> copy_cards(queue<int> ori, int n) {
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        q.push(ori.front());
        ori.pop();
    }
    return q;
}

pair<int, queue<int>> recursive_combat(queue<int> pc1, queue<int> pc2) {
    set<pair<queue<int>, queue<int>>> states;

    while (!(pc1.empty() || pc2.empty())) {
        states.insert({pc1, pc2});

        auto i1 = pc1.front();
        pc1.pop();
        auto i2 = pc2.front();
        pc2.pop();

        if (pc1.size() >= static_cast<size_t>(i1) && pc2.size() >= static_cast<size_t>(i2)) {
            auto [comp, _] = recursive_combat(copy_cards(pc1, i1), copy_cards(pc2, i2));
            if (comp == 1) {
                pc1.push(i1);
                pc1.push(i2);
            } else {
                pc2.push(i2);
                pc2.push(i1);
            }

        } else {
            if (i1 > i2) {
                pc1.push(i1);
                pc1.push(i2);
            } else {
                pc2.push(i2);
                pc2.push(i1);
            }
        }

        if (states.contains({pc1, pc2})) {
            return {1, pc1};
        }
        states.insert({pc1, pc2});
    }

    return pc1.empty() ? make_pair(2, pc2) : make_pair(1, pc1);
}

void part2() {
    ifstream input("input");
    string line;
    vector<queue<int>> player_card;
    queue<int> q;
    while (input.good()) {
        getline(input, line);
        if (line.empty() || input.eof()) {
            player_card.push_back(q);
            q = queue<int>{};
        } else if (line.contains("Player")) {
            continue;
        } else {
            q.push(stoi(line));
        }
    }

    auto [_, qf] = recursive_combat(player_card[0], player_card[1]);

    int re = 0;
    int n  = qf.size();
    while (!qf.empty()) {
        re += n * qf.front();
        qf.pop();
        --n;
    }

    cout << re << '\n';
}

int main() {
    part1();
    part2();
    return 0;
}