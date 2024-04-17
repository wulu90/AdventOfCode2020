#include <fstream>
#include <iostream>
#include <queue>
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

int main() {
    part1();
    return 0;
}