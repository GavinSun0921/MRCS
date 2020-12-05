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
    Simulator::log(Simulator::Point::MISS_DENSITY);
}

Simulator::Point::Point() : Simulator::Point(0, 0) {
    Simulator::log(Simulator::Point::MISS_COORDINATE);
}

double Simulator::Point::getX() const {
    return x;
}

void Simulator::Point::setX(double x) {
    Point::x = x;
}

double Simulator::Point::getY() const {
    return y;
}

void Simulator::Point::setY(double y) {
    Point::y = y;
}

int Simulator::Point::getDensity() const {
    return density;
}

void Simulator::Point::setDensity(int density) {
    Point::density = density;
}

void Simulator::Point::setCoordinate(double x, double y) {
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
    Simulator::log(Simulator::Field::ATTENTION);
}

Simulator::Field::Field(std::pair<double, double> centre) : Simulator::Field(centre, std::vector<Simulator::Point>()){
    Simulator::log(Simulator::Field::MISS_VECTOR);
}

Simulator::Field::Field(double x, double y) : Simulator::Field(std::make_pair(x, y)) {
    ;
}

Simulator::Field::Field() : Simulator::Field(0, 0) {
    Simulator::log(Simulator::Field::MISS_CENTRE);
}

void Simulator::Field::_radiationCount() {
    Simulator::log(Simulator::Field::CLEAR_COUNT);
    Simulator::Field::radiationCount.erase(
            Simulator::Field::radiationCount.begin(),
            Simulator::Field::radiationCount.end()
    );
}

void Simulator::Field::setCentre(const std::pair<double, double> &centre) {
    Field::centre = centre;
}

void Simulator::Field::setCentre(double x, double y) {
    Field::setCentre(std::make_pair(x, y));
}

void Simulator::Field::clearField() {
    Simulator::log(Simulator::Field::CLEAR_FIELD);
    Field::pointsInField.clear();
    Field::_radiationCount();
}

void Simulator::Field::addPoint(const Simulator::Point& point) {
    Field::pointsInField.push_back(point);
}

void Simulator::Field::addPoint(double x, double y, int density) {
    Field::addPoint(Point(x, y, density));
    Field::_radiationCount();
}

void Simulator::Field::addPoint(double x, double y) {
    Field::addPoint(Point(x, y));
}

double Simulator::Field::getRadiationCount(double r) {
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

Simulator::Field::~Field() {
    Simulator::log("----END----\n");
}

void Simulator::log(const std::string& message) {
    std::ofstream log;
    log.open("simulate.log", std::ios::app);

    if (log) {
        time_t now_time = time(nullptr);
        log << asctime(localtime(&now_time)) << "  | " << message << std::endl;
        log.close();
    } else {
        std::cout << "WARNING: Unable to write logfile." << std::endl;
        abort();
    }
}

void Simulator::resetLog() {
    std::ofstream log;
    log.open("simulate.log");

    if (log) {
        time_t now_time = time(nullptr);
        log << asctime(localtime(&now_time)) << "  | " << "logfile is reset." << std::endl;
        log.close();
    } else {
        std::cout << "WARNING: Unable to write logfile." << std::endl;
        abort();
    }
}
