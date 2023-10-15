/**
 * @parent include/OpenGL/mathObjects
 * @file PointND.h
 * @author ayano
 * @date 9/15/23
 * 
*/

#ifndef OPENGL_ndPoint_H
#define OPENGL_ndPoint_H

#include <string>
#include <cmath>
#include <array>
#include <sstream>
#include "spdlog/fmt/bundled/core.h"

template<std::size_t D>
class PointND {
public:
    /**
     * @brief the coordinate in cartesian form
     */
    std::array<float, D> coord = {};

    /**
     * @brief empty constructor
     */
    PointND() = default;

    /**
     * @brief initialize a ND point with the given coord
     * @param coord coordinate
     */
    explicit PointND(const std::array<float, D>& li);

    /**
     * @brief initializer_list version
     * @param coord coordinate
     */
    PointND(const std::initializer_list<float>& coord);

    /**
     * copy constructor
     * @param p another point
     */
    PointND(const PointND<D>& p);

    /**
     * move constructor
     * @param p another point
     */
    PointND(PointND<D>&& p) noexcept;

    /**
     * destructor
     */
    virtual ~PointND() = default;

    /**
     * @brief get the distance between two points
     * @param p another point
     * @return the distance
     */
    float dist(const PointND<D>& p) const;

    /**
     * @brief get the distance between two points, ref this if the distance is very big
     * @param p another point
     * @return the distance
     * @remark only ref this if the distance is extremely large
     */
    float distBig(const PointND<D>& p) const;

    /**
     * @brief move the point with the given transformation
     * @param trans how many unit you want to move in each coord
     */
    void transform(const std::array<float, D>& trans);

    /**
     * set the position of the point
     * @param pos point position
     */
    void setPos(const std::array<float, D>& pos);

    /**
     * set the position of the point with a point
     * @param point point position
     */
    void setPos(const PointND<D>& point);

    /**
     * get the dimension of the point
     * @return dimension
     */
    std::size_t dim() const;

    PointND<D> operator +(const PointND<D>& p);

    PointND<D> operator -(const PointND<D>& p);

    PointND<D>& operator =(const PointND<D>& other);
    
    PointND<D>& operator =(PointND<D>&& other) noexcept;

    virtual explicit operator std::string() const;
};

template<std::size_t D>
PointND<D>& PointND<D>::operator=(const PointND<D> &other) {
    coord = other.coord;
    return *this;
}

template<std::size_t D>
void PointND<D>::transform(const std::array<float, D>& trans) {
    for(int i = 0; i < D; i++){
        coord[i] += trans[i];
    }
}

template<std::size_t D>
PointND<D>::PointND(PointND &&p) noexcept {
    coord = std::move(p.coord);
}

template<std::size_t D>
PointND<D>::PointND(const std::array<float, D>& li) {
    if(li.size() != D) throw std::runtime_error(fmt::format("dimension unmatch! conflict between self dimension ({0}) and foreign dimension ({1})!", D, li.size()));
    coord = li;
}

template<std::size_t D>
std::size_t PointND<D>::dim() const {
    return D;
}

template<std::size_t D>
void PointND<D>::setPos(const std::array<float, D>& pos) {
    coord = pos;
}

template<std::size_t D>
void PointND<D>::setPos(const PointND<D>& point) {
    coord = point.coord;
}

template<std::size_t D>
PointND<D>::PointND(const PointND<D> &p) : coord(p.coord) {

}

template<std::size_t D>
float PointND<D>::distBig(const PointND<D> &p) const {
    float sum = 0;
    auto p_coord = p.coord();
    for (int i = 0; i < D; i++)
        sum += (coord[i] - p_coord[i]) * (coord[i] - p_coord[i]);
    return sqrt(sum);
}

template<std::size_t D>
float PointND<D>::dist(const PointND<D> &p) const {
    float sum = 0;
    auto p_coord = p.coord;
    for (int i = 0; i < D; i++)
        sum += (coord[i] - p_coord[i]) * (coord[i] - p_coord[i]);
    return sqrt(sum);
}


template<std::size_t D>
PointND<D>::PointND(const std::initializer_list<float> &coord){
    if(coord.size() != D) throw std::runtime_error(fmt::format("dimension unmatch! conflict between self dimension ({0}) and foreign dimension ({1})!", D, coord.size()));
    int idx = 0;
    for(auto i : coord){
        this->coord[idx] = i;
        idx++;
    }
}

template<std::size_t D>
PointND<D>::operator std::string() const {
    auto sout = std::stringstream();
    sout<< D << "D point at rectangular coord : (";
    for(int i = 0; i < D; i++){
        sout << coord[i];
        if(i != D - 1) sout << ", ";
    }
    sout << ")";
    return sout.str();
}

template<std::size_t D>
PointND<D> PointND<D>::operator+(const PointND<D> &p) {
    PointND<D> result;
    for (int i = 0; i < D; i++){
        result.coord[i] = coord[i] + p.coord[i];
    }
    return result;
}

template<std::size_t D>
PointND<D> PointND<D>::operator-(const PointND<D> &p) {
    PointND<D> result;
    for (int i = 0; i < D; i++){
        result.coord[i] = coord[i] - p.coord[i];
    }
    return result;
}

template<std::size_t D>
PointND<D>& PointND<D>::operator=(PointND<D>&& other) noexcept {
    if(this != &other) {
        coord = std::move(other.coord);
    }
    return *this;
}


#endif //OPENGL_ndPoint_H
