//
// Created by Gavin Sun on 2020/12/3.
//

#ifndef GRAIN_SIMULATE_NODE_H
#define GRAIN_SIMULATE_NODE_H

#include <iostream>
#include <cmath>

    class Node {
    private:
        double x, y;
        int density;
    public:
        Node(double x = 0, double y = 0, int density = 0);

        int getDensity() const;

        void setDensity(int density);

        double getX() const;

        void setX(double x);

        double getY() const;

        void setY(double y);

        bool operator<(const Node &rhs) const;

        bool operator>(const Node &rhs) const;

        bool operator<=(const Node &rhs) const;

        bool operator>=(const Node &rhs) const;

        bool operator==(const Node &rhs) const;

        bool operator!=(const Node &rhs) const;

        friend std::ostream &operator<<(std::ostream &os, const Node &node);

        double get_distance(const Node &rhs) const;
    };

#endif //GRAIN_SIMULATE_NODE_H
