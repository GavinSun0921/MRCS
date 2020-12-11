#include "src/Simulator3D.h"

int main() {
    // Creat a 'Field' named field.
    Simulator3D::Field field;

    // Put two points into field.
    field.addPoint(1, 1, 1, 1);
    field.addPoint(3, 3, 3, 1);

    // Make points in the field close to (0,0,0).
    field.prepare();

    // Calculate all unit in the three-dimensional matrix.
    // The maximum dimension is 'MAX_RESOLUTION' in file 'Simulator3D.h'.
    field.calculate();

    // Get the radiation count in the (0,0,0).
    std::cout << field.getCnt(0, 0, 0) << std::endl;

    // Get the radiation count in the plane of 'x=250'.
    field.outputX(250);
    // field.outputX("D:/pathdemo/data.txt", 250);
    // It will save the output to "D:/pathdemo/data.txt".

    return 0;
}