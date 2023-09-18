#include <mathObjects/Point3D.h>

Point3D::Point3D(const std::array<float, 3> &set): PointND(set), x(set[0]), y(set[1]), z(set[2]){

}

Point3D::Point3D(const float &x, const float &y, const float &z) : x(x), y(y), z(z){
    coord = std::array<float, 3>({x, y, z});
}
