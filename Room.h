#include <climits>
//
// Created by Gavin Sun on 2020/12/3.
//

#ifndef GRAIN_SIMULATE_ROOM_H
#define GRAIN_SIMULATE_ROOM_H

#include <vector>
#include <map>
#include <cmath>
#include <ostream>
#include "Node.h"

class Room {
private:
    const double infinitesimal_num = 1e4;
    int density;
    Node centre;
    std::vector<Node> pool;
    std::map<double, double> cnt;
public:
    Room();

    Room(int density, const Node &centre);

    Room(int density, const std::vector<Node> &pool);

    Room(const Node &centre, const std::vector<Node> &pool);

    Room(int density, const Node &centre, const std::vector<Node> &pool);

    Room(int density, std::vector<std::pair<double, double> > pool);

    const double getInfinitesimalNum() const;

    void setPool(const std::vector<Node> &pool);

    const std::vector<Node> &getPool() const;

    const Node &getCentre() const;

    void setCentre(const Node &centre);

    void setCentre(double x0 = 0, double y0 = 0);

    friend std::ostream &operator<<(std::ostream &os, const Room &room);

    bool operator==(const Room &rhs) const;

    bool operator!=(const Room &rhs) const;

    int getDensity() const;

    void setDensity(int density = 1);

    void push_back(const Node &node);

    void push_back(double x, double y);

    const std::map<double, double> &getCnt() const;

    void initCnt();

    double get_radiation_num(double r, int density);

    double get_radiation_num(double r);

    void init_buffer(std::vector<Node> &buffer, double r);
};

#endif //GRAIN_SIMULATE_ROOM_H
