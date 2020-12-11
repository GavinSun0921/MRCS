#include "Simulator3D.h"

int main() {
    Simulator3D::Field field;

    field.addPoint(1, 1, 1, 1);
    field.addPoint(3, 3, 3, 1);

    field.prepare();

    field.calculate();

    std::cout << field.getCnt(0, 0, 0) << std::endl;

    return 0;
}