#include "Room.h"

int main() {
    Room test;

    // the number of grains;
    int n;
    std::cin >> n;

    // give grains coordinate (x, y) in ordered;
    for (int i = 0; i < n; i++) {
        double x, y;
        std::cin >> x >> y;
        test.push_back(x, y);
    }

    // set density;
    // custom your own density degree in "Calculator.cpp" file with different fitting function.
    test.setDensity(); // without parameters is default '1';

    // set centre with coordinate (x0, y0);
    test.setCentre(); // without parameters is default '(0, 0)';

    // get the radiation count with a distance from centre
    test.get_radiation_num(1); // fill with the distance you want to get;

    return 0;
}
