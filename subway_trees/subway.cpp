#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<string> read_input();
bool equal(vector<int> v1, vector <int> v2);
vector<int> exploration_checksum(string exploration);

int main() {
    vector<string> scenarios = read_input();

    for (unsigned int i = 0; i < scenarios.size(); i += 2) {
        bool same_tree = equal(
            exploration_checksum(scenarios[i]),
            exploration_checksum(scenarios[i+1])
        );
        if (same_tree) {
            cout << "same";
        } else {
            cout << "different";
        }
        cout << endl;
    }

    return 0;
}

vector<string> read_input() {
    vector<string> strings;
    int scenarios; 
    cin >> scenarios;
    
    for (int i = 0; i < scenarios*2; i++) {
        string line;
        cin >> line;
        strings.push_back(line);
    }
    
    return strings;
}

bool equal(vector<int> v1, vector <int> v2) {
    if (v1.size() != v2.size()) {
        return false;
    }
    for (unsigned int i = 0; i < v1.size(); i++) {
        if (v1[i] != v2[i]) {
            return false;
        }
    }
    return true;
}

/*
 * Create checksum of resulting tree by following exploration.
 * Checksum is a vector of ints representing how many nodes
 * there are for each depth (steps from root node).
 */
vector<int> exploration_checksum(string exploration) {
    vector<int> checksum;
    unsigned int depth = 0;
    for (auto bit : exploration) {
        if (bit == '0') {
            if (checksum.size() <= depth) {
                checksum.push_back(0);
            }
            checksum[depth++]++;
        } else if (bit == '1') {
            depth--;
        }
    }
    return checksum;
}
