#include <iostream>

int main() {
    int frontc, rearc;
    vector<int> front, rear;

    while (cin >> frontc >> rearc) {
        set<double> ratios;

        for (int f = 0; f < frontc, f++) {
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

        for(auto it = ratios.begin(); it < ratios.end()-1; it++) {
            
        }

    }
        
    return 0;
}
