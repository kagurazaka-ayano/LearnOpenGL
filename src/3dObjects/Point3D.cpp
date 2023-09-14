#include <3dObjects/Point3D.h>

Point3D::Point3D(const float *&set): x(set[0]), y(set[1]), z(set[2]){

}

Point3D::Point3D(const float &x, const float &y, const float &z) : x(x), y(y), z(z){

}

Point3D Point3D::operator+(const Point3D &p) const {
    return Point3D{x + p.x, y+p.y, z+p.z};
}

Point3D Point3D::operator-(const Point3D &p) const {
    return Point3D{x-p.x, y-p.y, z-p.z};
}

Point3D::operator std::string() const {
    std::ostringstream oss;
    oss << "(" << x << ", " << y << ", " << z << ")";
    return oss.str();
}

float Point3D::dist(const Point3D &p) const {
    return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2) + pow(z + p.z, 2));
}

Point3D Point3D::normalize(int dim_x, int dim_y, int dim_z) const {
    return Point3D{x / dim_x * 2, y / dim_y * 2, z / dim_z * 2};
}

Point3D Point3D::operator+(const float *&shift) const {
    return Point3D{x + shift[0], y + shift[1], z + shift[2]};
}

Point3D Point3D::operator-(const float *&shift) const {
    return Point3D{x - shift[0], y - shift[1], z - shift[2]};
}




