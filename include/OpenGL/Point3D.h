//
// Created by Ayano Kagurazaka on 9/14/23.
//

#ifndef OPENGL_POINT3D_H
#define OPENGL_POINT3D_H

class Point3D {
private:
    double coord[3];
public:
    Point3D(const double& x, const double& y, const double& z){
        this->coord[0] = x;
        this->coord[1] = y;
        this->coord[2] = z;
    }

    double x()
};


#endif //OPENGL_POINT3D_H
