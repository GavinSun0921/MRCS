#include "Simulator.h"

int main() {
    // reset logfile.
    Simulator::resetLog();

    // creat a 'Field' named field;
    Simulator::Field field;

    // put two point into field;
    field.addPoint(1, 2, 1); // (x, y, density);
    // field.addPoint(2, 1); // without 'density' parameter, it will go addPoint(x, y, 0);

    // set centre;
    field.setCentre(0, 0); // (x, y);

    // get radiation count with 'r' = 1.
    field.getRadiationCount(1);

    return 0;
}
