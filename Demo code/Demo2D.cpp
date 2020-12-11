#include "../src/Simulator.h"

int main() {
    // Reset logfile.
    Simulator::resetLog();

    // Creat a 'Field' named field.
    Simulator::Field field;

    // Put two points into field.
    field.addPoint(1, 2, 1); // (x, y, density);
    // field.addPoint(2, 1); // without 'density' parameter, it will go addPoint(x, y, 0);

    // Set centre;
    field.setCentre(0, 0); // (x, y);

    // Get radiation count with 'r' = 1.
    field.getRadiationCount(1);

    return 0;
}
