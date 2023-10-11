/**
 * @parent include/OpenGL/utilities
 * @file utilities.h
 * @author ayano
 * @date 9/20/23
 * @brief utility class contains many useful functions
*/

#ifndef OPENGL_UTILITIES_H
#define OPENGL_UTILITIES_H

#include <array>
#include <iostream>
#include <unordered_map>
#include "spdlog/spdlog.h"
#include <sstream>
#include "glad/glad.h"

/**
 * @brief evaluate a whole bunch of statements, return -1 if everything is evaluated to true
 * @param expList list of expressions
 * @return index of the first false expression in this list, or -1 means everything is true
 */
inline int batchCheck(const std::initializer_list<bool>& expList);

/**
 * @brief assertion made in runtime, if the expression is evaluated false, will throw runtime error with given message
 * @param expression assertion expression, trigger runtime error if evaluated false
 * @param message message in runtime error
 * @remark the assertion happens in runtime, so if the expression consists exclusively compile-time values, ref static_assert instead
 */
inline void runtimeAssert(bool expression, const std::string& message);

/**
 * @brief change a dec number to hex
 * @param dec dec number
 * @return hex representation, in string
 */
inline std::string decToHex(int dec);

/**
 * @brief assertion made in runtime, if the expression is evaluated false, will throw runtime error with given message
 * @param expMap pair of expression-tested and message pending release
 * @remark the assertion happens in runtime, so if the expression consists exclusively compile-time values, ref static_assert instead
 */
void runtimeAssert(const std::unordered_map<bool, std::string>& expMap);

/**
 * @brief check whether GLAD is included
 */
inline void checkGLState();

/**
 * @brief slice an array with length N, step M elements from begin
 * @tparam T type of the elements
 * @tparam N length of input array
 * @tparam M count how many step from N
 * @param arr base array
 * @param begin begin element
 * @return sliced array
 * @remark begin must be less than the array size and non-negative
 */
template<typename T, std::size_t N, std::size_t M>
std::array<T, M> sliceArray(const std::array<T, N>& arr, std::size_t begin){
    runtimeAssert({
        {begin + M <= N, fmt::format("Slice index out of range, array has {0} elements but the slice is from {1} to {2}!", N, begin, begin + M)},
        {begin >= 0 && begin < N, fmt::format("Begin position must be less than array size and non-negative! (given begin = {0}, array size = {1})", begin, arr.size())}
    });
    std::array<T, M> ans;
    std::copy(arr.begin() + begin, arr.begin() + M, ans.begin());
    return ans;
}

/**
 * @brief slice an array with length N, step M elements from begin
 * @tparam T type of the elements
 * @tparam M count how many step from N
 * @param arr base array
 * @param begin begin element
 * @return sliced array
 * @remark begin must be less than the array size and non-negative
 */
template<typename T, std::size_t M>
std::array<T, M> sliceArray(const std::initializer_list<T>& arr, std::size_t begin){
    runtimeAssert({
        {begin + M <= arr.size(), fmt::format("Slice index out of range, array has {0} elements but the slice is from {1} to {2}!", arr.size(), begin, begin + M)},
        {M < arr.size() && M > 0, fmt::format("Sliced element count must be less than array size and greater than 0! (given M = {0}, array size = {1})", M, arr.size())},
        {begin < arr.size(), fmt::format("Begin position must be less than array size and non-negative! (given begin = {0}, array size = {1})", begin, arr.size())}
    });
    std::array<T, M> ans;
    std::copy(arr.begin() + begin, arr.begin() + M, ans.begin());
    return ans;
}

inline void runtimeAssert(bool expression, const std::string& message){
    if(!expression) {
        spdlog::critical(message);
        throw std::runtime_error(message);
    }
}

inline int batchCheck(const std::initializer_list<bool>& expList){
    int idx = 0;
    for(auto i : expList){
        if(!i) return idx;
        idx++;
    }
    return -1;
}

inline std::string decToHex(int dec) {
    auto ss = std::stringstream();
    ss << std::hex << dec;
    return ss.str();
}

void checkGLState() {
    if (glGetString == nullptr) throw std::runtime_error("GLAD must be initialized in order to generate shader objects");
}

#endif //OPENGL_UTILITIES_H
