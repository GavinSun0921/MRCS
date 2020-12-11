//
// Created by Gavin Sun on 2020/12/11.
//

#ifndef GRAIN_SIMULATE_SIMULATOR3D_H
#define GRAIN_SIMULATE_SIMULATOR3D_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include "Calculator.h"
#include <ctime>
#include <fstream>
#include <dirent.h>
#include <unistd.h>

namespace Simulator3D {
    class Point {
    private:
        double x, y, z;
        int density;
    public:
        Point(double x, double y, double z, int density);

        Point(double x, double y, double z);

        Point();

        double getX() const;

        void setX(double x);

        double getY() const;

        void setY(double y);

        double getZ() const;

        void setZ(double z);

        int getDensity() const;

        void setDensity(int density);

        void setCoordinate(double x, double y, double z);

        bool operator==(const Point &rhs) const;

        bool operator!=(const Point &rhs) const;

        Point &operator=(const Point &rhs);
    };

    class Field {
    private:
        static const int MAX_RESOLUTION = 500;
        static const int MAX_SIZE = 20;
        constexpr static const double SCALING = MAX_SIZE * 1.0 / MAX_RESOLUTION;

        double x0{}, y0{}, z0{};
        std::vector<Simulator3D::Point> pointsInField;
//        double cnt[MAX_RESOLUTION][MAX_RESOLUTION][MAX_RESOLUTION]{};
        double ***cnt;

        void translationPoints(double x, double y, double z);

        void translationPoints();

        static double getDistance(const Point &u, int x, int y, int z);

        static double calculate(const Point &u, int x, int y, int z);

        double calculate(int x, int y, int z);

        void output(const std::string& path, int index, int val);

    public:
        Field();

        double getX0() const;

        void setX0(double x0);

        double getY0() const;

        void setY0(double y0);

        double getZ0() const;

        void setZ0(double z0);

        const std::vector<Simulator3D::Point> &getPointsInField() const;

        void addPoint(double x, double y, double z, int density);

        double getCnt(int x, int y, int z);

        void prepare();

        void calculate();

        void outputX(const std::string& path, int val);

        void outputY(const std::string& path, int val);

        void outputZ(const std::string& path, int val);

        void outputX(int val);

        void outputY(int val);

        void outputZ(int val);
    };
};


#endif //GRAIN_SIMULATE_SIMULATOR3D_H
