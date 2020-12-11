//
// Created by Gavin Sun on 2020/12/3.
//

#include "Calculator.h"

double Calculator::calculate(double dist, int density) {
    switch (density) {
        case 1:
            return calculate_with_density_1(dist);
        case 2:
            return calculate_with_density_2(dist);
        case 3:
            return calculate_with_density_3(dist);
        case 4:
            return calculate_with_density_4(dist);
        case 5:
            return calculate_with_density_5(dist);
        case 6:
            return calculate_with_density_6(dist);
        default:
            std::cout << "Warning: can't match any density!" << std::endl;
    }
    return 0;
}

double Calculator::calculate_with_density_1(double dist) {
    return dist;
}

double Calculator::calculate_with_density_2(double dist) {
    return 0;
}

double Calculator::calculate_with_density_3(double dist) {
    return 0;
}

double Calculator::calculate_with_density_4(double dist) {
    return 0;
}

double Calculator::calculate_with_density_5(double dist) {
    return 0;
}

double Calculator::calculate_with_density_6(double dist) {
    return 0;
}

double Calculator::Gamma(double xx) {
    double x(xx), y(xx);
    double tmp = x + 5.5;
    tmp -= (x + 0.5) * log(tmp);
    double ser = Calculator::SER;
    for (int i = 0; i < 6; i++) {
        ser += Calculator::COF[i] / (++y);
    }
    return xx * exp((-tmp + log(Calculator::COE * ser / x)));
}
