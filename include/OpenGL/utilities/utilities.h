/*
 * @parent: src/utilities
 * @file: utilities.h
 * @author: ayano
 * @date: 9/20/23
 * 
*/

#ifndef OPENGL_UTILITIES_H
#define OPENGL_UTILITIES_H

#include <array>
#include <iostream>
#include <cassert>

template<typename T, std::size_t N, std::size_t M>
std::array<T, M> sliceArray(const std::array<T, N>& arr, std::size_t begin){
    static_assert(begin + M <= N && begin >= 0 && M >= 0);
    std::array<T, M> ans;
    std::copy(arr.begin() + begin, arr.begin() + M, ans.begin());
    return ans;
}

template<typename T, std::size_t M>
std::array<T, M> sliceArray(const std::initializer_list<T>& arr, std::size_t begin){
    assert(begin + M <= arr.size() && M < arr.size() && begin < arr.size() && begin >= 0 && M > 0);
    std::array<T, M> ans;
    std::copy(arr.begin() + begin, arr.begin() + M, ans.begin());
    return ans;
}

template<typename T, std::size_t N>
std::array<T, N> toArray(const std::initializer_list<T>& list) {
    assert(list.size() == N);
    std::array<T, N> arr;
    std::copy(list.begin(), list.end(), arr.begin());
    return arr;
}

#endif //OPENGL_UTILITIES_H
