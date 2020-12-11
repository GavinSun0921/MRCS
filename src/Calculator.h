//
// Created by Gavin Sun on 2020/12/3.
//

#ifndef GRAIN_SIMULATE_CALCULATOR_H
#define GRAIN_SIMULATE_CALCULATOR_H

#include <iostream>
#include <cmath>

class Calculator {
private:
    constexpr static const double COF[6] = {76.18009172947146, -86.50532032941677, 24.01409824083091, -1.231739572450155, 0.1208650973866179e-2,
                                  -0.5395239384953e-5};
    constexpr static const double SER = 1.000000000190015;
    constexpr static const double COE = 2.5066282746310005;
public:
    static double calculate(double dist, int density);

    static double calculate_with_density_1(double dist);

    static double calculate_with_density_2(double dist);

    static double calculate_with_density_3(double dist);

    static double calculate_with_density_4(double dist);

    static double calculate_with_density_5(double dist);

    static double calculate_with_density_6(double dist);

    static double Gamma(double x);
};


#endif //GRAIN_SIMULATE_CALCULATOR_H
