/*
 * @parent: src/mathObjects
 * @file: Color.cpp
 * @author: ayano
 * @date: 9/24/23
 *
*/

#include "mathObjects/Color.h"

Color::Color(const float &x, const float &y, const float &z, const float &a, IColorSpace* space) : PointND<4>(Color::checkValue({x, y, z, a}, space)){
    this->rh = x;
    this->gs = y;
    this->bvl = z;
    this->a = a;
    this->space = space;
}

Color::Color(std::string hex) : space(ColorSpaceRGB::Instance()) {
    runtimeAssert({
                          {hex.starts_with('#'), "Invalid hexadecimal number form, hexadecimal for color must start with '#' character (like #add8e6)"},
                          {hex.size() == 7 || hex.size() == 9 || hex.size() == 4, fmt::format("Incorrect length, size without '#' must be either 3, 6 or 8 (got {0})", hex.size() - 1)}
    });
    hex = hex.substr(1, hex.size() - 1);
    switch (hex.size()) {
        case 6:
            rh = stoi(hex.substr(0, 2), nullptr, 16) / 255.0f;
            gs = stoi(hex.substr(2, 2), nullptr, 16) / 255.0f;
            bvl = stoi(hex.substr(4, 2), nullptr, 16) / 255.0f;
            a = 1;
            Color::checkValue({rh, gs, bvl, a}, space);
            break;
        case 8:
            rh = stoi(hex.substr(0, 2), nullptr, 16) / 255.0f;
            gs = stoi(hex.substr(2, 2), nullptr, 16) / 255.0f;
            bvl = stoi(hex.substr(4, 2), nullptr, 16) / 255.0f;
            a = stoi(hex.substr(6, 2), nullptr, 16) / 255.0f;
            break;
        case 3:
            rh = stoi(hex.substr(0, 1), nullptr, 16) / 255.0f;
            rh = stoi(hex.substr(1, 1), nullptr, 16) / 255.0f;
            rh = stoi(hex.substr(2, 1), nullptr, 16) / 255.0f;
            a = 1;
            break;
    }
    coord = {rh, gs, bvl, a};
}

Color::Color(const std::array<float, 4> &set, IColorSpace* space): Color(set[0], set[1], set[2], set[3], space) {

}

Color::Color(const std::array<float, 3> &set, IColorSpace* space): Color(set[0], set[1], set[2], 1, space) {

}

Color::Color(const Color &other) : Color(other.rh, other.gs, other.bvl, other.a, other.space){

}

Color::Color(Color &&other) noexcept : PointND<4>(std::move(other)), rh(other.rh), gs(other.gs), bvl(other.bvl), a(other.a), space(other.space){

}

Color::Color(const float &x, const float &y, const float &z, IColorSpace* space) : Color(x, y, z, 1, space) {

}

Color::Color(const float &r, const float &g, const float &b, const float &a) : Color(r, g, b, a,
                                                                                     ColorSpaceRGB::Instance()) {

}

Color::Color(const float &r, const float &g, const float &b) : Color(r, g, b, 1, ColorSpaceRGB::Instance()) {

}

Color::Color() : Color(Color::WHITE) {

}

const Color Color::BLACK = Color(0, 0, 0, ColorSpaceRGB::Instance());

const Color Color::WHITE = Color(1, 1, 1, ColorSpaceRGB::Instance());

Color::operator std::string() const {
    int r = static_cast<int>(this->rh * 255), g = static_cast<int>(this->gs * 255), b = static_cast<int>(this->bvl * 255), a = static_cast<int>(this->a * 255);
    return fmt::format("#{0}{1}{2}", decToHex(r), decToHex(g), decToHex(b), decToHex(a));
}

std::array<float, 4> ColorSpaceRGB::convertTo(const std::array<float, 4> &color, IColorSpace* dest) const {
    float r = color[0], g = color[1], b = color[2], a = color[3];
    float max = std::max({r, g, b});
    float min = std::min({r, g, b});
    float diff = max - min;
    if (dest == ColorSpaceRGB::Instance()){
        return color;
    }
    else if (dest == ColorSpaceHSV::Instance()){
        float h, s, v;
        if (diff == 0) h = 0.0f;
        else if (max == r) h = 60.0f * fmod((g - b) / diff, 6);
        else if (max == g) h = 60.0f * ((b - r)/diff + 2);
        else h = 60.0f * ((r - g) / diff + 4);
        s = (max == 0) ? 0: diff / max;
        v = max;
        if (h < 0) h += 360;
        return std::array{h, s, v, a};
    }
    else if (dest == ColorSpaceHSL::Instance()){
        float h, s, l;
        l = (max + min) / 2;
        s = (l == 0 || l == 1) ? 0: ((max - l) / std::min(l, 1 - l));
        if (diff == 0) h = 0.0f;
        else if (max == r) h = 60.0f * fmod((g - b) / diff, 6);
        else if (max == g) h = 60.0f * ((b - r)/diff + 2);
        else if (max == b) h = 60.0f * ((r - g) / diff + 4);
        if (h < 0) h += 360;
        return std::array{h, s, l, a};
    }
    else{
        spdlog::critical("Color space unsupported, only RGB, HSV, HSL are supported");
        throw std::runtime_error("Color space unsupported, only RGB, HSV, HSL are supported");
    }
}

bool ColorSpaceRGB::checkData(const std::array<float, 4> &color, bool throwExp) const {
    float r = color[0], g = color[1], b = color[2], a = color[3];
    auto messages = std::array<std::string, 4>{
        fmt::format("R value of RGB color must be in the interval [0, 1] in degree! Get {0}", r),
        fmt::format("G value of RGB color must be in the interval [0, 1], get {0}!", g),
        fmt::format("B value of RGB color must be in the interval [0, 1], get {0}!", b),
        fmt::format("A value of RGB color must be in the interval [0, 1], get {0}!", a)
    };
    int exp = batchCheck({
                             within(0, r, 1, true, true),
                             within(0, g, 1, true, true),
                             within(0, b, 1, true, true),
                             within(0, a, 1, true, true)
                     });
    if (!throwExp) {
        return exp == -1;
    }
    if (exp == -1) return true;
    throw std::runtime_error(messages[exp]);
}

std::array<float, 4> ColorSpaceHSV::convertTo(const std::array<float, 4> &color, IColorSpace* dest) const {
    float h = color[0], s = color[1], v = color[2], a = color[3];
    checkData(color);
    if (dest == ColorSpaceHSV::Instance()) {
        return color;
    }
    else if(dest == ColorSpaceHSL::Instance()){
        float l = v * (1 - s / 2);
        return {
            h,
            (l == 0 || l == 1) ? 0 : ((v - l) / std::min(l, 1 - l)),
            l,
            a
        };
    }

    else if(dest == ColorSpaceRGB::Instance()){
        float c = v * s;
        float hi = h / 60;
        float x = c * (1 - abs(fmod(hi, 2) - 1));
        float m = v - c;
        std::array<float, 4> ans = std::array<float, 4>();
        if (within(0, hi, 1)) ans = {c, x, 0, a};
        else if (within(1, hi, 2)) ans = {x, c, 0, a};
        else if (within(2, hi, 3)) ans = {0, c, x, a};
        else if (within(3, hi, 4)) ans = {0, x, c, a};
        else if (within(4, hi, 5)) ans = {x, 0, c, a};
        else if (within(5, hi, 6)) ans = {c, 0, x, a};
        for (int i = 0; i < 3; ++i) {
            ans[i] += m;
        }
        return ans;
    }
    else{
        spdlog::critical("Color space unsupported, only RGB, HSV, HSL are supported");
        throw std::runtime_error("Color space unsupported, only RGB, HSV, HSL are supported");
    }
}

bool ColorSpaceHSV::checkData(const std::array<float, 4> &color, bool throwExp) const {
    float h = color[0], s = color[1], v = color[2], a = color[3];
    int exp = batchCheck({
                       within(0, h, 360, true, true),
                       within(0, s, 1, true, true),
                       within(0, v, 1, true, true),
                       within(0, a, 1, true, true)
               });
    auto messages = std::array<std::string, 4>{
            fmt::format("H value of HSV color must be in the interval [0, 360] in degree! Get {0}", h),
            fmt::format("S value of HSV color must be in the interval [0, 1], get {0}!", s),
            fmt::format("V value of HSV color must be in the interval [0, 1], get {0}!", v),
            fmt::format("A value of HSV color must be in the interval [0, 1], get {0}!", a)
    };
    if (!throwExp) {
        return exp == -1;
    }
    if (exp == -1) return true;
    throw std::runtime_error(messages[exp]);
}

std::array<float, 4> ColorSpaceHSL::convertTo(const std::array<float, 4> &color, IColorSpace* dest) const {
    float h = color[0], s = color[1], l = color[2], a = color[3];
    checkData(color);
    if (dest == ColorSpaceHSL::Instance()){
        return color;
    }
    else if(dest == ColorSpaceHSV::Instance()){
        float v = l + s * std::min(l, 1 - l);
        return {
            h,
            (v == 0) ? 0 : 2 * (1 - l / v),
            v,
            a
        };
    }
    else if(dest == ColorSpaceRGB::Instance()){
        auto f = [h, s, l](float n){
            float k = fmodf(n + h / 30, 12);
            float a = s * std::min(l, 1 - l);
            return l - a * std::max(-1.0f, std::min({k - 3, 9 - k, 1.0f}));
        };
        return {f(0), f(8), f(4), a};
    }
    else{
        spdlog::critical("Color space unsupported, only RGB, HSV, HSL are supported");
        throw std::runtime_error("Color space unsupported, only RGB, HSV, HSL are supported");
    }
}

bool ColorSpaceHSL::checkData(const std::array<float, 4> &color, bool throwExp) const {
    float h = color[0], s = color[1], l = color[2], a = color[3];
    int exp = batchCheck({
                                 within(0, h, 360, true, true),
                                 within(0, s, 1, true, true),
                                 within(0, l, 1, true, true),
                                 within(0, a, 1, true, true)
                         });
    auto messages = std::array<std::string, 4>{
            fmt::format("H value of HSL color must be in the interval [0, 360] in degree! Get {0}", h),
            fmt::format("S value of HSL color must be in the interval [0, 1], get {0}!", s),
            fmt::format("L value of HSL color must be in the interval [0, 1], get {0}!", l),
            fmt::format("A value of HSL color must be in the interval [0, 1], get {0}!", a)
    };
    if (!throwExp) {
        return exp == -1;
    }
    if (exp == -1) return true;
    throw std::runtime_error(messages[exp]);
}

std::array<float, 4> IColorSpace::convertFrom(const std::array<float, 4> &color, IColorSpace *from) {
    return from->convertTo(color, this);
}

std::array<float, 4> IColorSpace::convert(IColorSpace *from, const std::array<float, 4> &color, IColorSpace *to) {
    return from->convertTo(color, to);
}

IColorSpace * Color::getSpace() const {
    return space;
}

std::array<float, 4> Color::checkValue(const std::array<float, 4> &color, IColorSpace *spaceIn) {
    if(spaceIn->checkData(color))
        return color;
}

Color& Color::operator=(Color&& other) noexcept{
    if (this != &other){
        rh = other.rh;
        gs = other.gs;
        bvl = other.bvl;
        a = other.a;
        space = other.space;
    }
    return *this;
}

Color& Color::operator=(const Color& other){
    if(this != &other){
        this->rh = other.rh;
        this->gs = other.gs;
        this->bvl = other.bvl;
        this->a = other.a;
        this->space = other.space;
        PointND<4>::operator=(other);
    }
    return *this;
}


