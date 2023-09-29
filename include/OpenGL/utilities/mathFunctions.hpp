/*
 * @parent: include/OpenGL/utilities
 * @file: mathFunctions.h
 * @author: ayano
 * @date: 9/25/23
 * 
*/

#ifndef OPENGL_MATHFUNCTIONS_HPP
#define OPENGL_MATHFUNCTIONS_HPP

inline int sgn(float n);

inline int heaviside(float n);

inline constexpr bool within(float low, float comp, float high, bool lInclusive = true, bool rInclusive = false);

inline int sgn(float n){
    return n >= 0 ? (n == 0) ? 0 : -1 : 1;
}

inline int heaviside(float n){
    return n >= 0 ? 1: 0;
}

inline constexpr bool within(float low, float comp, float high, bool lInclusive, bool rInclusive) {
    return (low < comp || (low <= comp && lInclusive)) && (comp < high || (comp <= high && rInclusive));
}

#endif //OPENGL_MATHFUNCTIONS_HPP
