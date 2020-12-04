#include <climits>
//
// Created by Gavin Sun on 2020/12/3.
//

#include "Room.h"
#include "Calculator.h"

void Room::setPool(const std::vector<Node> &pool) {
    Room::pool = pool;
}

void Room::push_back(const Node &node) {
    this->pool.push_back(node);
}

const std::vector<Node> &Room::getPool() const {
    return pool;
}

int Room::getDensity() const {
    return density;
}

void Room::setDensity(int density) {
    Room::density = density;
}

bool Room::operator==(const Room &rhs) const {
    return density == rhs.density;
}

bool Room::operator!=(const Room &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Room &room) {
    os << "density: " << room.density << std::endl;
    os << "pool: " << std::endl;
    for (auto i : room.getPool()) {
        std::cout << i << std::endl;
    }
    return os;
}

void Room::initCnt() {
    cnt.erase(cnt.begin(), cnt.end());
}

double Room::get_radiation_num(double r) {
    if (cnt.count(r)) {
        return cnt[r];
    } else {
        double tmp = 0;

        std::vector<Node> buffer;
        Room::init_buffer(buffer, r);
        for (auto u : buffer) {
            for (auto v : pool) {
                double dist = u.get_distance(v);
                tmp += Calculator::calculate(dist, Room::density) / Room::infinitesimal_num;
            }
        }

        cnt[r] = tmp;
        return cnt[r];
    }
}

const Node &Room::getCentre() const {
    return centre;
}

void Room::setCentre(const Node &centre) {
    Room::centre = centre;
}

double Room::get_radiation_num(double r, int de) {
    setDensity(density);
    return get_radiation_num(r);
}

void Room::setCentre(double x0, double y0) {
    centre = Node(x0, y0);
}

void Room::init_buffer(std::vector<Node> &buffer, double r) {
    const double pi = std::acos(-1);
    const double step = 2 * pi / Room::infinitesimal_num;
    double x0 = centre.getX();
    double y0 = centre.getY();
    for (double theta = 0; theta < 2 * pi; theta += step) {
        double nx = x0 + r * cos(theta);
        double ny = y0 + r * sin(theta);
        buffer.push_back(Node(nx, ny));
    }
}

const double Room::getInfinitesimalNum() const {
    return infinitesimal_num;
}

Room::Room(int density, const Node &centre, const std::vector<Node> &pool) : density(density), centre(centre),
                                                                             pool(pool) {
    std::cout << "Attention:" << std::endl;
    std::cout << "Set 'infinitesimal_num' to " << Room::getInfinitesimalNum() << "." << std::endl;
}

Room::Room(const Node &centre, const std::vector<Node> &pool) : centre(centre), pool(pool) {
    std::cout << "Attention:" << std::endl;
    std::cout << "Set 'infinitesimal_num' to " << Room::getInfinitesimalNum() << "." << std::endl;
    std::cout << "Your 'density' is set to 1." << std::endl;
    setDensity(1);
}

Room::Room(int density, const std::vector<Node> &pool) : density(density), pool(pool) {
    std::cout << "Attention:" << std::endl;
    std::cout << "Set 'infinitesimal_num' to " << Room::getInfinitesimalNum() << "." << std::endl;
    std::cout << "Your 'centre' is set to (0, 0)." << std::endl;
    setCentre();
}

Room::Room(int density, const Node &centre) : density(density), centre(centre) {
    std::cout << "Attention:" << std::endl;
    std::cout << "Set 'infinitesimal_num' to " << Room::getInfinitesimalNum() << "." << std::endl;
    std::cout << "Your 'pool' don't have any 'Point'." << std::endl;
}

Room::Room() {
    std::cout << "Attention:" << std::endl;
    std::cout << "Set 'infinitesimal_num' to " << Room::getInfinitesimalNum() << "." << std::endl;
    std::cout << "Your 'density' is set to 1." << std::endl;
    setDensity(1);
    std::cout << "Your 'centre' is set to (0, 0)." << std::endl;
    setCentre();
    std::cout << "Your 'pool' don't have any 'Point'." << std::endl;
}

Room::Room(int density, std::vector<std::pair<double, double>> pool) : density(density) {
    std::cout << "Attention:" << std::endl;
    std::cout << "Set 'infinitesimal_num' to " << Room::getInfinitesimalNum() << "." << std::endl;
    std::cout << "Your 'centre' is set to (0, 0)." << std::endl;
    setCentre();
    for (auto i : pool) {
        Room::push_back(Node(i.first, i.second));
    }
}

void Room::push_back(double x, double y) {
    Room::push_back(Node(x, y));
}

const std::map<double, double> &Room::getCnt() const {
    return Room::cnt;
}
