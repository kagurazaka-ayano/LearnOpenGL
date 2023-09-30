/*
 * @parent: include/OpenGL/mathObjects
 * @file: Color.h
 * @author: ayano
 * @date: 9/24/23
 * generic color class
*/

#ifndef OPENGL_COLOR_H
#define OPENGL_COLOR_H

#include <mathObjects/PointND.h>
#include <utilities/utilities.h>
#include <utilities/SingletonAbstract.hpp>
#include <utilities/mathFunctions.hpp>
#include <typeinfo>
#include <typeindex>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cmath>

/**
 * @brief abstract color space class used in the strategy mode
 */
class IColorSpace {
public:
    /**
     * @brief convertTo function that will be implemented in each concrete implementation of color space
     * @param color a color list with 4 units, normally last one will be alpha value(except in CMYK color spaces but it
     * probably won't be supported)
     * @param dest which color space the color you are converting to, must be a derived class of IColorSpace
     * @return the converted color
     * @remark all the derived classes must be made as Singleton by publicly inherit SingletonAbstract class, made
     * constructor private, and delete copy constructor and equal sign
     */
    virtual std::array<float, 4> convertTo(const std::array<float, 4>& color, IColorSpace* dest) const = 0;
    virtual bool checkData(const std::array<float, 4> &color, bool throwExp = true) const = 0;
    std::array<float, 4> convertFrom(const std::array<float, 4>& color, IColorSpace* from);
    static std::array<float, 4> convert(IColorSpace* from, const std::array<float, 4>& color, IColorSpace* to);
};

/**
 * @brief RGB color space
 */
class ColorSpaceRGB : public IColorSpace, public SingletonAbstract<ColorSpaceRGB> {
    friend class SingletonAbstract<ColorSpaceRGB>;
private:
    ColorSpaceRGB() = default;
public:
    bool checkData(const std::array<float, 4> &color, bool throwExp = true) const override;
    ColorSpaceRGB(ColorSpaceRGB& other) = delete;
    ColorSpaceRGB& operator=(ColorSpaceRGB& other) = delete;
    std::array<float, 4> convertTo(const std::array<float, 4>& color, IColorSpace* dest) const override;
};

/**
 * @brief HSV color space
 */
class ColorSpaceHSV : public IColorSpace, public SingletonAbstract<ColorSpaceHSV> {
    friend class SingletonAbstract<ColorSpaceHSV>;
private:
    ColorSpaceHSV() = default;
public:
    bool checkData(const std::array<float, 4> &color, bool throwExp = true) const override;
    ColorSpaceHSV(ColorSpaceHSV& other) = delete;
    ColorSpaceHSV& operator=(ColorSpaceHSV& other) = delete;
    std::array<float, 4> convertTo(const std::array<float, 4>& color, IColorSpace* dest) const override;
};

/**
 * @brief HSL color space
 */
class ColorSpaceHSL : public IColorSpace, public SingletonAbstract<ColorSpaceHSL>{
    friend class SingletonAbstract<ColorSpaceHSL>;
private:
    ColorSpaceHSL() = default;
public:
    bool checkData(const std::array<float, 4> &color, bool throwExp = true) const override;
    ColorSpaceHSL(ColorSpaceHSL& other) = delete;
    ColorSpaceHSL& operator=(ColorSpaceHSL& other) = delete;
    std::array<float, 4> convertTo(const std::array<float, 4>& color, IColorSpace* dest) const override;
};

/**
 * @brief generic color class, supports RGB, HSV, HSL color spaces with alpha channel enabled
 */
class Color : public PointND<4>{
public:
    float rh, gs, bvl, a;

    float data[4]{0};

    Color(const float& x, const float& y, const float& z, const float& a, IColorSpace* space);

    Color(const float& x, const float& y, const float& z, IColorSpace* space);

    Color(const float& r, const float& g, const float& b, const float& a);

    Color(const float& r, const float& g, const float& b);

    Color(const Color& other);

    Color(Color&& other) noexcept;

    explicit Color(std::string hex);

    explicit Color(const std::array<float, 4>& set, IColorSpace* space);

    explicit Color(const std::array<float, 3>& set, IColorSpace* space);

    Color();

    /**
     * @brief change to the given color space
     * @param newSpace color space you wish to convertTo
     */
    void convertColorSpace(IColorSpace* newSpace);

    /**
     * @brief get current color space
     * @return color space
     */
    IColorSpace * getSpace() const;

    // predefined colors
    const static Color WHITE;

    const static Color BLACK;

    /**
     * @remark tostring
     * @return hexadecimal representation (including alpha value) of this color
     */
    explicit operator std::string() const;

    Color& operator=(Color&& other) noexcept;

    Color& operator=(const Color& other);


private:
    IColorSpace* space;

    static std::array<float, 4> checkValue(const std::array<float, 4>& color, IColorSpace* spaceIn);
};



#endif //OPENGL_COLOR_H
