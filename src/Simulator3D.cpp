//
// Created by Gavin Sun on 2020/12/11.
//

#include "Simulator3D.h"

Simulator3D::Point::Point(double x, double y, double z, int density) : x(x), y(y), z(z), density(density) {
    ;
}

Simulator3D::Point::Point(double x, double y, double z) : Simulator3D::Point(x, y, z, 0) {
    ;
}

Simulator3D::Point::Point() : Simulator3D::Point(0, 0, 0) {
    ;
}

double Simulator3D::Point::getX() const {
    return x;
}

void Simulator3D::Point::setX(double x) {
    Point::x = x;
}

double Simulator3D::Point::getY() const {
    return y;
}

void Simulator3D::Point::setY(double y) {
    Point::y = y;
}

double Simulator3D::Point::getZ() const {
    return z;
}

void Simulator3D::Point::setZ(double z) {
    Point::z = z;
}

int Simulator3D::Point::getDensity() const {
    return density;
}

void Simulator3D::Point::setDensity(int density) {
    Point::density = density;
}

void Simulator3D::Point::setCoordinate(double x, double y, double z) {
    Simulator3D::Point::setX(x);
    Simulator3D::Point::setY(y);
    Simulator3D::Point::setZ(z);
}

bool Simulator3D::Point::operator==(const Simulator3D::Point &rhs) const {
    return Simulator3D::Point::x == rhs.x &&
           Simulator3D::Point::y == rhs.y &&
           Simulator3D::Point::z == rhs.z &&
           Simulator3D::Point::density == rhs.density;
}

bool Simulator3D::Point::operator!=(const Simulator3D::Point &rhs) const {
    return !(rhs == *this);
}

Simulator3D::Point &Simulator3D::Point::operator=(const Simulator3D::Point &rhs) {
    Simulator3D::Point::x = rhs.x;
    Simulator3D::Point::y = rhs.y;
    Simulator3D::Point::z = rhs.z;
    return *this;
}

Simulator3D::Field::Field() {
    int size = Simulator3D::Field::MAX_SIZE;
    setX0(size / 2);
    setY0(size / 2);
    setZ0(size / 2);
    cnt = new double **[Simulator3D::Field::MAX_RESOLUTION];
    for (int i = 0; i < Simulator3D::Field::MAX_RESOLUTION; i++) {
        cnt[i] = new double *[Simulator3D::Field::MAX_RESOLUTION];
    }
    for (int i = 0; i < Simulator3D::Field::MAX_RESOLUTION; i++) {
        for (int j = 0; j < Simulator3D::Field::MAX_RESOLUTION; j++) {
            cnt[i][j] = new double[Simulator3D::Field::MAX_RESOLUTION];
        }
    }
    for (int i = 0; i < Simulator3D::Field::MAX_RESOLUTION; i++) {
        for (int j = 0; j < Simulator3D::Field::MAX_RESOLUTION; j++) {
            for (int k = 0; k < Simulator3D::Field::MAX_RESOLUTION; k++) {
                cnt[i][j][k] = -1;
            }
        }
    }
}

void Simulator3D::Field::addPoint(double x, double y, double z, int density) {
    Simulator3D::Field::pointsInField.emplace_back(x, y, z, density);
}

void Simulator3D::Field::translationPoints(double x, double y, double z) {
    double delta_x = Simulator3D::Field::x0 - x;
    double delta_y = Simulator3D::Field::y0 - y;
    double delta_z = Simulator3D::Field::z0 - z;
    for (auto &ele : Simulator3D::Field::pointsInField) {
        double nx = ele.getX() + delta_x;
        double ny = ele.getY() + delta_y;
        double nz = ele.getZ() + delta_z;
        ele.setCoordinate(nx, ny, nz);
    }
}

void Simulator3D::Field::translationPoints() {
    double x = 0, y = 0, z = 0;
    for (auto ele : Simulator3D::Field::pointsInField) {
        x += ele.getX();
        y += ele.getY();
        z += ele.getZ();
    }
    double size = Simulator3D::Field::pointsInField.size() * 1.0;
    x /= std::max(1.0, size);
    y /= std::max(1.0, size);
    z /= std::max(1.0, size);
    Simulator3D::Field::translationPoints(x, y, z);
}

double Simulator3D::Field::getX0() const {
    return x0;
}

void Simulator3D::Field::setX0(double x0) {
    Field::x0 = x0;
}

double Simulator3D::Field::getY0() const {
    return y0;
}

void Simulator3D::Field::setY0(double y0) {
    Field::y0 = y0;
}

double Simulator3D::Field::getZ0() const {
    return z0;
}

void Simulator3D::Field::setZ0(double z0) {
    Field::z0 = z0;
}

const std::vector<Simulator3D::Point> &Simulator3D::Field::getPointsInField() const {
    return pointsInField;
}

double Simulator3D::Field::getDistance(const Simulator3D::Point &u, int x, int y, int z) {
    double nx = x * Simulator3D::Field::SCALING;
    double ny = y * Simulator3D::Field::SCALING;
    double nz = z * Simulator3D::Field::SCALING;
    return std::sqrt(
            (u.getX() - nx) * (u.getX() - nx) +
            (u.getY() - ny) * (u.getY() - ny) +
            (u.getZ() - nz) * (u.getZ() - nz)
    );
}

double Simulator3D::Field::calculate(const Simulator3D::Point &u, int x, int y, int z) {
    double dist = Simulator3D::Field::getDistance(u, x, y, z);
    int density = u.getDensity();
    return Calculator::calculate(dist, density);
}

double Simulator3D::Field::calculate(int x, int y, int z) {
    double ans = 0;
    for (auto &ele : Simulator3D::Field::pointsInField) {
        ans += Simulator3D::Field::calculate(ele, x, y, z);
    }
    return ans;
}

double Simulator3D::Field::getCnt(int x, int y, int z) {
    if (Simulator3D::Field::cnt[x][y][z] == -1) {
        Simulator3D::Field::cnt[x][y][z] = Simulator3D::Field::calculate(x, y, z);
    }
    return Simulator3D::Field::cnt[x][y][z];
}

void Simulator3D::Field::prepare() {
    Simulator3D::Field::translationPoints();
}

void Simulator3D::Field::calculate() {
    long long tot = Simulator3D::Field::MAX_RESOLUTION * Simulator3D::Field::MAX_RESOLUTION *
                    Simulator3D::Field::MAX_RESOLUTION;
    long long cnt = 0, per = 0;
    for (int x = 0; x < Simulator3D::Field::MAX_RESOLUTION; x++) {
        for (int y = 0; y < Simulator3D::Field::MAX_RESOLUTION; y++) {
            for (int z = 0; z < Simulator3D::Field::MAX_RESOLUTION; z++) {
                Simulator3D::Field::cnt[x][y][z] = Simulator3D::Field::calculate(x, y, z);
                cnt++;
                if (100 * cnt / tot > per) {
                    per = 100 * cnt / tot;
                    printf("\rCalculating - %lld%%", per);
                    fflush(stdout);
                }
            }
        }
    }
    puts("");
}

void Simulator3D::Field::output(const std::string &path, int index, int val) {
    std::ofstream out(path);
    if (out.is_open()) {
        out << std::fixed << std::setprecision(Simulator3D::Field::PRECISION);
        for (int i = 0; i < Simulator3D::Field::MAX_RESOLUTION; i++) {
            for (int j = 0; j < Simulator3D::Field::MAX_RESOLUTION; j++) {
                double value;
                if (index == 0) value = Simulator3D::Field::cnt[val][i][j];
                if (index == 1) value = Simulator3D::Field::cnt[i][val][j];
                if (index == 2) value = Simulator3D::Field::cnt[i][j][val];
                out << value << " ";
            }
            out << "\n";
        }
        out.close();
    } else {
        std::cout << "Can't open file " << path << std::endl;
    }
}

void Simulator3D::Field::outputX(const std::string &path, int val) {
    Simulator3D::Field::output(path, 0, val);
}

void Simulator3D::Field::outputY(const std::string &path, int val) {
    Simulator3D::Field::output(path, 1, val);
}

void Simulator3D::Field::outputZ(const std::string &path, int val) {
    Simulator3D::Field::output(path, 2, val);
}

void Simulator3D::Field::outputX(int val) {
    char buffer[255];
    getcwd(buffer, sizeof(buffer));
    std::string path = buffer;
    path = path + "/Xlayer" + std::to_string(val) + ".txt";
    std::cout << Simulator3D::Field::MISS_PATH << path << std::endl;
    Simulator3D::Field::outputX(path, val);
}

void Simulator3D::Field::outputY(int val) {
    char buffer[255];
    getcwd(buffer, sizeof(buffer));
    std::string path = buffer;
    path = path + "/Ylayer" + std::to_string(val) + ".txt";
    std::cout << Simulator3D::Field::MISS_PATH << path << std::endl;
    Simulator3D::Field::outputY(path, val);
}

void Simulator3D::Field::outputZ(int val) {
    char buffer[255];
    getcwd(buffer, sizeof(buffer));
    std::string path = buffer;
    path = path + "/Zlayer" + std::to_string(val) + ".txt";
    std::cout << Simulator3D::Field::MISS_PATH << path << std::endl;
    Simulator3D::Field::outputZ(path, val);
}

const int Simulator3D::Field::getMAX_RESOLUTION() {
    return MAX_RESOLUTION;
}
