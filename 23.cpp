#include <iostream>
#include <map>
#include <set>
#include <string>
using namespace std;

struct cup {
    int id;
    cup* next;
};

void part1() {
    string input = "942387615";

    map<int, cup*> id_p;
    set<int> idset;

    cup* head = new cup;
    cup* curr = new cup;
    head->id  = input[0] - '0';
    curr      = head;

    id_p.insert({head->id, head});
    idset.insert(head->id);

    for (size_t i = 1; i < 9; ++i) {
        cup* c     = new cup;
        c->id      = input[i] - '0';
        curr->next = c;
        curr       = c;

        id_p.insert({c->id, c});
        idset.insert(c->id);
    }

    curr->next = head;

    int currid = head->id;

    for (int i = 0; i < 100; ++i) {
        set<int> pick_idset;

        int pickup_id  = id_p[currid]->next->id;
        int pickend_id = pickup_id;

        idset.erase(pickup_id);
        pick_idset.insert(pickup_id);

        for (int j = 0; j < 2; ++j) {
            pickend_id = id_p[pickend_id]->next->id;
            pick_idset.insert(pickend_id);
            idset.erase(pickend_id);
        }

        int picknext_id = id_p[pickend_id]->next->id;

        id_p[currid]->next = id_p[picknext_id];

        bool id_minus = false;
        int dest      = currid - 1;
        for (int j = currid - 1; j > 0; --j) {
            if (idset.contains(j)) {
                id_minus = true;
                dest     = j;
                break;
            }
        }

        dest = id_minus ? dest : *idset.crbegin();

        id_p[pickend_id]->next = id_p[dest]->next;

        id_p[dest]->next = id_p[pickup_id];

        currid = id_p[currid]->next->id;

        for (auto j : pick_idset) {
            idset.insert(j);
        }
    }

    string ans;

    curr = id_p[1];
    for (int i = 1; i < 9; ++i) {
        ans.push_back(curr->next->id + '0');
        curr = curr->next;
    }

    cout << ans << '\n';

    delete head;
    delete curr;
}

void part2() {
    string input = "942387615";

    map<int, cup*> id_p;

    cup* head = new cup;
    cup* curr = new cup;
    head->id  = input[0] - '0';
    curr      = head;

    id_p.insert({head->id, head});

    for (size_t i = 1; i < 9; ++i) {
        cup* c     = new cup;
        c->id      = input[i] - '0';
        curr->next = c;
        curr       = c;

        id_p.insert({c->id, c});
    }

    for (int i = 10; i <= 1000000; ++i) {
        cup* c     = new cup;
        c->id      = i;
        curr->next = c;
        curr       = c;

        id_p.insert({i, c});
    }

    curr->next = head;

    int currid = head->id;

    for (int i = 0; i < 10000000; ++i) {
        set<int> pick_idset;

        int pickup_id  = id_p[currid]->next->id;
        int pickend_id = pickup_id;

        pick_idset.insert(pickup_id);

        for (int j = 0; j < 2; ++j) {
            pickend_id = id_p[pickend_id]->next->id;
            pick_idset.insert(pickend_id);
        }

        int picknext_id = id_p[pickend_id]->next->id;

        id_p[currid]->next = id_p[picknext_id];

        bool id_minus = false;
        int dest      = currid - 1;
        for (int j = currid - 1; j > 0; --j) {
            if (!pick_idset.contains(j)) {
                id_minus = true;
                dest     = j;
                break;
            }
        }

        if (!id_minus) {
            dest = 1000000;
            for (int j = 1000000; j > 0; --j) {
                if (!pick_idset.contains(j)) {
                    dest = j;
                    break;
                }
            }
        }

        id_p[pickend_id]->next = id_p[dest]->next;

        id_p[dest]->next = id_p[pickup_id];

        currid = id_p[currid]->next->id;
    }

    int64_t ans = static_cast<int64_t>(id_p[1]->next->id) * static_cast<int64_t>(id_p[1]->next->next->id);
    cout << ans << '\n';

    delete head;
    delete curr;
}

int main() {
    part1();
    part2();
    return 0;
}