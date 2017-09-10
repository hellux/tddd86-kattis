#include <iostream>
#include <sstream>
#include <map>

using namespace std;

#define MAX_LENGTH 23 /* word(10) + space + word + newline + null */

/*
 * Algorithm:
 *  -insert entries to map with the foreign word as key
 *  -check if foreign word is in map (with map.find)
 */
int main() {
    char buffer[MAX_LENGTH];
    map<string, string> dictionary;

    while (fgets(buffer, MAX_LENGTH, stdin)[0] != '\n') {
        stringstream ss;
        ss.str(buffer);
        string eng, foreign;
        ss >> eng >> foreign;
        dictionary[foreign] = eng;
    }

    string foreign;
    while (cin >> foreign) {
        if (dictionary.find(foreign) != dictionary.end()) {
            cout << dictionary[foreign] << endl;
        } else {
            cout << "eh" << endl;
        }
    }
    
    return 0;
}
