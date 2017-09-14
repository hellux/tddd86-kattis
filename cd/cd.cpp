#include <iostream>
#include <set>

using namespace std;

int main() {
    unsigned jack, jill;

    while (cin >> jack >> jill) {
        if (jack == 0 && jill == 0) break;

        set<unsigned> jack_catalog;

        for (unsigned i = 0; i < jack; i++) {
            unsigned cat_num;
            cin >> cat_num;
            jack_catalog.insert(cat_num);
        }

        unsigned sell = 0;
        for (unsigned i = 0; i < jill; i++) {
            unsigned cat_num;
            cin >> cat_num;
            if (jack_catalog.find(cat_num) != jack_catalog.end()) {
                sell++;
            }
        }

        cout << sell << '\n';
    }
}
