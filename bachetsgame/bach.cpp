#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main() {
    int stones;
    int m;

    while (cin >> stones >> m) {
        int amounts[m] = {};
        for (int i = 0; i < m; i++) {
            cin >> amounts[i];
        }

        bool wins[stones+1] = {};
        for (int i = 1; i <= stones; i++) {
            for (auto amount : amounts) {
                int index = i - amount;
                if (index >= 0 && !wins[index]) {
                    wins[i] = true;
                    break;
                }
            }
        }
        
        cout << (wins[stones] ? "Stan" : "Ollie") << " wins" << endl;
    }

    return 0;
}
