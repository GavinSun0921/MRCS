//
// Created by Gavin Sun on 2020/12/3.
//

#include "Node.h"

double Node::getX() const {
    return x;
}

void Node::setX(double x) {
    Node::x = x;
}

double Node::getY() const {
    return y;
}

void Node::setY(double y) {
    Node::y = y;
}

bool Node::operator<(const Node &rhs) const {
    return std::tie(x, y) < std::tie(rhs.x, rhs.y);
}

bool Node::operator>(const Node &rhs) const {
    return rhs < *this;
}

bool Node::operator<=(const Node &rhs) const {
    return !(rhs < *this);
}

bool Node::operator>=(const Node &rhs) const {
    return !(*this < rhs);
}

bool Node::operator==(const Node &rhs) const {
    return std::tie(x, y) == std::tie(rhs.x, rhs.y);
}

bool Node::operator!=(const Node &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Node &node) {
    os << "x: " << node.getX() << " y: " << node.getY();
    return os;
}

double Node::get_distance(const Node &rhs) const {
    return sqrt((x-rhs.x)*(x-rhs.x) + (y-rhs.y)*(y-rhs.y));
}

Node::Node(double x, double y, int density) : x(x), y(y), density(density) {}

int Node::getDensity() const {
    return density;
}

void Node::setDensity(int density) {
    Node::density = density;
}

