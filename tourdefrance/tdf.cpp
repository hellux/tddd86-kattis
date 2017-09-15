#include <iostream>
#include <iterator>
#include <vector>
#include <set>

using namespace std;

int main() {
    int frontc, rearc;

    while (cin >> frontc >> rearc) {
        vector<int> front, rear;
        set<double> ratios;

        for (int f = 0; f < frontc; f++) {
            int fr;
            cin >> fr;
            front.push_back(fr);
        }
        for (int r = 0; r < rearc; r++) {
            int re;
            cin >> re;
            front.push_back(re);
        }

        for (int r = 0; r < rearc; r++) {
            for (int f = 0; f < frontc; f++) {
                double ratio = (double) rear[r] / front[f];
                ratios.insert(ratio);
            }
        }
        
        double max_spread = 0;
        auto it = ratios.begin();
        while (next(it) != ratios.end()) {
            if (next(it) == ratios.end()) break;
            double spread = *next(it) / *it;
            if (spread > max_spread) {
                max_spread = spread;
            }
            it++;
        }

        printf("%.2f\n", max_spread);
    }
        
    return 0;
}
