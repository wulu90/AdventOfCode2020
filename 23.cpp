#include <iostream>
#include <map>
#include <set>
#include <string>
using namespace std;

struct cup {
    int id;
    cup* prev;
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
        c->prev    = curr;
        curr       = c;

        id_p.insert({c->id, c});
        idset.insert(c->id);
    }

    curr->next = head;
    head->prev = curr;

    curr = head;

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

        id_p[currid]->next      = id_p[picknext_id];
        id_p[picknext_id]->prev = id_p[currid];

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

        id_p[dest]->next->prev = id_p[pickend_id];
        id_p[pickend_id]->next = id_p[dest]->next;

        id_p[dest]->next      = id_p[pickup_id];
        id_p[pickup_id]->prev = id_p[dest];

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
}

int main() {
    part1();
    return 0;
}