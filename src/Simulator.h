//
// Created by Gavin Sun on 2020/12/4.
//

#ifndef MRCS_SIMULATOR_H
#define MRCS_SIMULATOR_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include "Calculator.h"
#include <ctime>
#include <fstream>

namespace Simulator {
    class Point {
    private:
        const std::string MISS_COORDINATE = "Warning: Missing parameter 'x' and 'y', default set to coordinate (0,0).";
        const std::string MISS_DENSITY = "Warning: Missing parameter 'density', default set to '0'.";

        double x, y;
        int density;
    public:
        Point(double x, double y, int density);

        Point(double x, double y);

        Point();

        double getX() const;

        void setX(double x);

        double getY() const;

        void setY(double y);

        int getDensity() const;

        void setDensity(int density);

        void setCoordinate(double x, double y);

        bool operator==(const Point &rhs) const;

        bool operator!=(const Point &rhs) const;

        Point &operator=(const Point &rhs);
    };

    class Field {
    private:
        const double INFINITESIMAL_NUM = 1e4;
        const std::string ATTENTION = "Attention: During calculating, infinitesimal number set to 10,000.";
        const std::string MISS_VECTOR = "Warning: Missing parameter 'pointsInField'(std::vector<Point>), default your field doesn't have any 'Point'.";
        const std::string MISS_CENTRE = "Warning: Missing parameter 'centre', default set centre to coordinate (0,0).";
        const std::string CLEAR_COUNT = "Attention: Radiation Count has cleared.";
        const std::string CLEAR_FIELD = "Attention: Points in Field has cleared.";

        std::pair<double, double> centre;
        std::vector<Point> pointsInField;
        std::map<double, double> radiationCount;

        void _radiationCount();

        void addPoint(const Point &point);

        std::vector<std::pair<double, double> > getPoints(double r) const;

        double calculate(const std::vector<std::pair<double, double> > &buffer);

        static double calculate(const Point &u, std::pair<double, double> v);

        static double getDistance(const Point &u, std::pair<double, double> v);

        static double getDistance(std::pair<double, double> u, std::pair<double, double> v);

    public:
        Field(std::pair<double, double> centre, std::vector<Point> pointsInField);

        explicit Field(std::pair<double, double> centre);

        Field(double x, double y);

        Field();

        virtual ~Field();

        void setCentre(const std::pair<double, double> &centre);

        void setCentre(double x, double y);

        void clearField();

        void addPoint(double x, double y, int density);

        void addPoint(double x, double y);

        double getRadiationCount(double r);
    };

    static void log(const std::string &);

    void resetLog();
}

#endif //MRCS_SIMULATOR_H
