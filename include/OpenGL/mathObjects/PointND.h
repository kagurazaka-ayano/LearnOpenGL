/*
 * @parent: src/mathObjects
 * @file: PointND.h
 * @author: ayano
 * @date: 9/15/23
 * 
*/

#ifndef OPENGL_ndPoint_H
#define OPENGL_ndPoint_H

#include <string>
#include <cmath>
#include <array>
#include <spdlog/fmt/bundled/core.h>

template<unsigned long D>
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
    explicit PointND(const std::array<float, D>& coord);

    /**
     * @brief initialize a ND point with the given coord
     * @param coord coordinate
     */
    PointND(const std::initializer_list<float>& li);

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
     * @brief get the distance between two points, use this if the distance is very big
     * @param p another point
     * @return the distance
     * @remark only use this if the distance is extremely large
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
    unsigned long dim() const;

    PointND<D> operator +(const PointND<D>& p) const;

    PointND<D> operator -(const PointND<D>& p) const;

    explicit operator std::string() const;

    friend std::ostream& operator<<(std::ostream& os, const PointND<D>& p);
};


#endif //OPENGL_ndPoint_H
