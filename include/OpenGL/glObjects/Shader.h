/**
 * @parent: include/OpenGL/glObjects
 * @file: Shader.h
 * @author: ayano
 * @date: 9/20/23
 * 
*/

#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H
#include <string>
#include <unordered_map>
#include <utility>
#include <typeindex>
#include <typeinfo>
#include <variant>

#include "glad/glad.h"
#include "spdlog/spdlog.h"
#include "mathObjects/PointND.h"
#include "utilities/mathFunctions.hpp"
#include "utilities/PoolAbstract.h"

/**
 * @brief base shader class, with its life cycle being managed by ShaderManager
 */
class BaseShader : public IPoolable{
public:
    virtual ~BaseShader();

protected:
    BaseShader(const std::string& name, unsigned int ID);
};

class FragShader : public BaseShader{
public:
    FragShader(const unsigned int &object, const std::string& name);
};

class VertShader : public BaseShader{
public:
    VertShader(const unsigned int &object, const std::string& name);
};

class GeomShader : public BaseShader{
public:
    GeomShader(const unsigned int &object, const std::string& name);
};

class ShaderProgram : public BaseShader {
public:
    /**
     * use the program
     */
    void use() const;

    ShaderProgram(const unsigned int &object, const std::string &name);

    /**
     * @brief generic way of setting a uniform value that belongs to standard types(int, float, bool)
     * @tparam T value type
     * @param varName uniform variable name
     * @param val value of that variable
     */
    template<typename T>
    void setUniformValue(const std::string &varName, T val) const;

    /**
     * @brief generic way of setting a uniform value that is a vector
     * @tparam C dimension of the vector, must be between 1 and 4
     * @param varName variable name
     * @param value value of the variable
     */
    template<std::size_t C>
    void setVectorValue(const std::string &varName, const PointND<C> &value) const;

private:

    template<typename T>
    constexpr void checkValidType() const;

    const std::unordered_map<std::type_index, std::variant<PFNGLUNIFORM1IPROC, PFNGLUNIFORM1FPROC>> STANDARD_FUNC_REF = {
            {typeid(int), glUniform1i},
            {typeid(float), glUniform1f},
            {typeid(bool), glUniform1i}
    };
    const std::array<PFNGLUNIFORM1FVPROC, 4> VEC_FUNC_REF = {glUniform1fv, glUniform2fv, glUniform3fv, glUniform4fv};
};


#endif //OPENGL_SHADER_H
