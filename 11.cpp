#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int adjacent_occupied(const vector<string>& seats, int row, int col) {
    static vector<pair<int, int>> adjs{{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
    int rownum = seats.size();
    int colnum = seats.front().size();

    int count = 0;
    for (auto [r, c] : adjs) {
        auto i = row + r;
        auto j = col + c;
        if (i >= 0 && i < rownum && j >= 0 && j < colnum && seats[i][j] == '#') {
            ++count;
        }
    }
    return count;
}

int first_see_occupied(const vector<string>& seats, int row, int col) {
    static vector<pair<int, int>> adjs{{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
    int rownum = seats.size();
    int colnum = seats.front().size();

    int count = 0;

    for (auto [r, c] : adjs) {
        int step = 1;

        while (true) {
            auto i = row + r * step;
            auto j = col + c * step;
            if (i < 0 || i >= rownum || j < 0 || j >= colnum) {
                break;
            }
            if (seats[i][j] == '#') {
                ++count;
                break;
            } else if (seats[i][j] == 'L') {
                break;
            } else {
                ++step;
            }
        }
    }

    return count;
}

void part1() {
    ifstream input("input");
    vector<string> seats;
    for (string line; getline(input, line);) {
        seats.push_back(line);
    }

    while (true) {
        vector<string> tmp = seats;

        for (size_t i = 0; i < seats.size(); ++i) {
            for (size_t j = 0; j < seats.front().size(); ++j) {
                switch (seats[i][j]) {
                case 'L':
                    if (adjacent_occupied(seats, i, j) == 0) {
                        tmp[i][j] = '#';
                    }
                    break;
                case '#':
                    if (adjacent_occupied(seats, i, j) >= 4) {
                        tmp[i][j] = 'L';
                    }
                    break;
                default:
                    break;
                }
            }
        }

        if (tmp == seats) {
            break;
        }
        seats = tmp;
    }

    int occupied_count = 0;
    for (size_t i = 0; i < seats.size(); ++i) {
        for (size_t j = 0; j < seats.front().size(); ++j) {
            if (seats[i][j] == '#') {
                ++occupied_count;
            }
        }
    }

    cout << occupied_count << '\n';
}

void part2() {
    ifstream input("input");
    vector<string> seats;
    for (string line; getline(input, line);) {
        seats.push_back(line);
    }

    while (true) {
        vector<string> tmp = seats;

        for (size_t i = 0; i < seats.size(); ++i) {
            for (size_t j = 0; j < seats.front().size(); ++j) {
                switch (seats[i][j]) {
                case 'L':
                    if (first_see_occupied(seats, i, j) == 0) {
                        tmp[i][j] = '#';
                    }
                    break;
                case '#':
                    if (first_see_occupied(seats, i, j) >= 5) {
                        tmp[i][j] = 'L';
                    }
                    break;
                default:
                    break;
                }
            }
        }

        if (tmp == seats) {
            break;
        }
        seats = tmp;
    }

    int occupied_count = 0;
    for (size_t i = 0; i < seats.size(); ++i) {
        for (size_t j = 0; j < seats.front().size(); ++j) {
            if (seats[i][j] == '#') {
                ++occupied_count;
            }
        }
    }

    cout << occupied_count << '\n';
}

int main() {
    part1();
    part2();
    return 0;
}