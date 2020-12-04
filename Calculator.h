//
// Created by Gavin Sun on 2020/12/3.
//

#ifndef GRAIN_SIMULATE_CALCULATOR_H
#define GRAIN_SIMULATE_CALCULATOR_H

#include <iostream>
#include <cmath>

class Calculator {
public:
    static double calculate(double dist, int density);
    static double calculate_with_density_1(double dist);
    static double calculate_with_density_2(double dist);
    static double calculate_with_density_3(double dist);
    static double calculate_with_density_4(double dist);
    static double calculate_with_density_5(double dist);
    static double calculate_with_density_6(double dist);
};


#endif //GRAIN_SIMULATE_CALCULATOR_H
