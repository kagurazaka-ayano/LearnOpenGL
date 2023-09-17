/*
 * @parent: src/mathObjects
 * @file: Point.cpp
 * @author: ayano
 * @date: 9/15/23
 * point in N dimension, with general math support
*/

#include <mathObjects/PointND.h>

template<unsigned long D>
void PointND<D>::transform(const std::array<float, D>& trans) {
    for(int i = 0; i < D; i++){
        coord[i] += trans[i];
    }
}

template<unsigned long D>
PointND<D>::PointND(PointND &&p) noexcept {
    coord = std::move(p.coord);
}

template<unsigned long D>
PointND<D>::PointND(const std::initializer_list<float> &li) {
    if(li.size() != D) throw std::exception(fmt::format("dimension unmatch! conflict between self dimension ({0}) and foreign dimension ({1})!", D, li.size()));
    coord = li;
}

template<unsigned long D>
PointND<D> PointND<D>::operator+(const PointND<D> &p) const {
    checkDimension(p);
    auto p_coord = p.coord;
    for (int i = 0; i < D; i++){
        p_coord[i] += coord[i];
    }
    return PointND(p_coord);
}

template<unsigned long D>
unsigned long PointND<D>::dim() const {
    return D;
}

template<unsigned long D>
void PointND<D>::setPos(const std::array<float, D>& pos) {
    coord = pos;
}

template<unsigned long D>
void PointND<D>::setPos(const PointND<D>& point) {
    coord = point.coord;
}

template<unsigned long D>
float PointND<D>::distBig(const PointND<D> &p) const {
    float sum = 0;
    auto p_coord = p.coord();
    for (int i = 0; i < D; i++)
        sum += (coord[i] - p_coord[i]) * (coord[i] - p_coord[i]);
    return sqrt(sum);
}

template<unsigned long D>
float PointND<D>::dist(const PointND<D> &p) const {
    float sum = 0;
    auto p_coord = p.coord();
    for (int i = 0; i < D; i++)
        sum += (coord[i] - p_coord[i]) * (coord[i] - p_coord[i]);
    return sqrt(sum);
}

template<unsigned long D>
PointND<D>::PointND(const PointND<D> &p) {
    this(p.coord);
}

template<unsigned long D>
PointND<D>::PointND(const std::array<float, D> &coord) {
    PointND(PointND(coord));
}

template<unsigned long D>
PointND<D>::operator std::string() const {
    std::string ans = static_cast<char>(D) + "D point at cart coord : (";
    for(int i = 0; i < D; i++){
        ans += static_cast<char>(coord[i]);
    }
    ans += ")";
    return ans;
}

template<unsigned long D>
PointND<D> PointND<D>::operator-(const PointND<D> &p) const {
    float* newPos[D]{};
    for(int i = 0; i < D; i++){
        newPos[i] = coord[i] - p.coord[i];
    }
    PointND<D> result(newPos);
    return PointND<D>(newPos);
}

template<unsigned long D>
std::ostream &operator<<(std::ostream &os, const PointND<D> &p) {
    os << std::string(p);
    return os;
}
