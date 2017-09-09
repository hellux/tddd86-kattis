#include <iostream>
#include <set>

using namespace std;

int main() {
    set<unsigned long> jack_catalog;
    unsigned long jack, jill;
    cin >> jack >> jill;

    for (unsigned long i = 0; i < jack; i++) {
        unsigned long cat_num;
        cin >> cat_num;
        jack_catalog.insert(cat_num);
    }

    unsigned long sell = 0;
    for (unsigned long i = 0; i < jill; i++) {
        unsigned long cat_num;
        cin >> cat_num;
        if (jack_catalog.find(cat_num) != jack_catalog.end()) {
            sell++;
        }
    }

    cout << sell << endl;
}
