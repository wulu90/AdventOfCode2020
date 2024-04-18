#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int64_t calc_loop_size(int64_t pub_key) {
    int64_t va      = 1;
    int64_t subject = 7;
    int64_t ans     = 0;

    while (true) {
        ++ans;
        va *= subject;
        va %= 20201227;
        if (va == pub_key) {
            break;
        }
    }
    return ans;
}

int64_t trans(int64_t subject, int64_t loop_size) {
    int64_t ans = 1;
    for (int64_t i = 1; i <= loop_size; ++i) {
        ans *= subject;
        ans %= 20201227;
    }
    return ans;
}

void part1() {
    ifstream input("input");
    int64_t card_pub_key;
    int64_t door_pub_key;
    input >> card_pub_key;
    input >> door_pub_key;

    // int64_t card_loop_size = calc_loop_size(card_pub_key);
    int64_t door_loop_size = calc_loop_size(door_pub_key);

    cout << trans(card_pub_key, door_loop_size) << '\n';
}

int main() {
    part1();
    return 0;
}