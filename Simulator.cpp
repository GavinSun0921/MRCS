#include <__bit_reference>
//
// Created by Gavin Sun on 2020/12/4.
//

#include "Simulator.h"

#include <utility>

Simulator::Point::Point(double x, double y, int density) : x(x), y(y), density(density) {
    ;
}

Simulator::Point::Point(double x, double y) : Simulator::Point(x, y, 0){
    std::cout << Simulator::Point::MISS_DENSITY << std::endl;
}

Simulator::Point::Point() : Simulator::Point(0, 0) {
    std::cout << Simulator::Point::MISS_COORDINATE << std::endl;
}

double Simulator::Point::getX() const {
    return x;
}

__unused void Simulator::Point::setX(double x) {
    Point::x = x;
}

double Simulator::Point::getY() const {
    return y;
}

__unused void Simulator::Point::setY(double y) {
    Point::y = y;
}

int Simulator::Point::getDensity() const {
    return density;
}

__unused void Simulator::Point::setDensity(int density) {
    Point::density = density;
}

__unused void Simulator::Point::setCoordinate(double x, double y) {
    Point::x = x;
    Point::y = y;
}

bool Simulator::Point::operator==(const Simulator::Point &rhs) const {
    return x == rhs.x &&
           y == rhs.y &&
           density == rhs.density;
}

bool Simulator::Point::operator!=(const Simulator::Point &rhs) const {
    return !(rhs == *this);
}

Simulator::Point &Simulator::Point::operator=(const Simulator::Point &rhs) {
    x = rhs.x;
    y = rhs.y;
    density = rhs.density;
    return *this;
}

Simulator::Field::Field(std::pair<double, double>  centre, std::vector<Point> pointsInField) : centre(std::move(centre)),
                                                                                     pointsInField(std::move(
                                                                                             pointsInField)) {
    std::cout << Simulator::Field::ATTENTION << std::endl;
}

Simulator::Field::Field(std::pair<double, double> centre) : Simulator::Field(centre, std::vector<Simulator::Point>()){
    std::cout << Simulator::Field::MISS_VECTOR << std::endl;
}

Simulator::Field::Field(double x, double y) : Simulator::Field(std::make_pair(x, y)) {
    ;
}

Simulator::Field::Field() : Simulator::Field(0, 0) {
    std::cout << Simulator::Field::MISS_CENTRE << std::endl;
}

__unused void Simulator::Field::_radiationCount() {
    std::cout << Simulator::Field::CLEAR_COUNT << std::endl;
    Simulator::Field::radiationCount.erase(
            Simulator::Field::radiationCount.begin(),
            Simulator::Field::radiationCount.end()
    );
}

void Simulator::Field::setCentre(const std::pair<double, double> &centre) {
    Field::centre = centre;
}

__unused void Simulator::Field::setCentre(double x, double y) {
    Field::setCentre(std::make_pair(x, y));
}

__unused void Simulator::Field::clearField() {
    std::cout << Simulator::Field::CLEAR_FIELD << std::endl;
    Field::pointsInField.clear();
    Field::_radiationCount();
}

void Simulator::Field::addPoint(const Simulator::Point& point) {
    Field::pointsInField.push_back(point);
}

__unused void Simulator::Field::addPoint(double x, double y, int density) {
    Field::addPoint(Point(x, y, density));
    Field::_radiationCount();
}

__unused void Simulator::Field::addPoint(double x, double y) {
    Field::addPoint(Point(x, y));
}

__unused double Simulator::Field::getRadiationCount(double r) {
    if (!Field::radiationCount.count(r)) {
        std::vector<std::pair<double, double> > buffer = Field::getPoints(r);
        radiationCount[r] = calculate(buffer);
    }
    return Field::radiationCount[r];
}

std::vector<std::pair<double, double> > Simulator::Field::getPoints(double r) const {
    std::vector<std::pair<double, double> > ret;
    const double PI = acos(-1);
    double x0 = Field::centre.first;
    double y0 = Field::centre.second;
    for (double theta = 0; theta < 2 * PI; theta += 2 * PI / Field::INFINITESIMAL_NUM) {
        double nx = x0 + r * cos(theta);
        double ny = y0 + r * sin(theta);
        ret.emplace_back(nx, ny);
    }
    return ret;
}

double Simulator::Field::calculate(const std::vector<std::pair<double, double>> &buffer) {
    double ans = 0;
    for (const auto &u : Field::pointsInField) {
        for (auto v : buffer) {
            ans += calculate(u, v) / Field::INFINITESIMAL_NUM;
        }
    }
    return ans;
}

double Simulator::Field::calculate(const Simulator::Point &u, std::pair<double, double> v) {
    double dist = Field::getDistance(u, v);
    int density = u.getDensity();
    return Calculator::calculate(dist, density);
}

double Simulator::Field::getDistance(const Simulator::Point &u, std::pair<double, double> v) {
    double x0 = u.getX();
    double y0 = u.getY();
    return Field::getDistance(std::make_pair(x0, y0), v);
}

double Simulator::Field::getDistance(std::pair<double, double> u, std::pair<double, double> v) {
    double deltaX = u.first - v.first;
    double deltaY = u.second - v.second;
    return std::sqrt(deltaX * deltaX + deltaY * deltaY);
}
