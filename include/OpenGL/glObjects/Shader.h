/*
 * @parent: src/glObjects
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
#include <glad/glad.h>

#include <spdlog/spdlog.h>
#include <mathObjects/PointND.h>
#include <utilities/mathFunctions.hpp>

/**
 * a shader class for internal use, will later implement reference counter
 */

class BaseShader{
public:
    const std::string name;
    const unsigned int ID;

    /**
     * @brief dispose the shader
     * @remark it will make its ref counter -1, and trigger manual gc if the ref counter == 0
     */
    void dispose();

    virtual ~BaseShader();

protected:
    unsigned int refCount = 0;

    BaseShader(std::string name, unsigned int ID);
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
    ShaderProgram(const unsigned int &object, const std::string &name);

    /**
     * use this program, and increment the ref counter by 1
     */
    void use();

    /**
     * @brief generic way of setting a uniform value that belongs to standard types(int, float, bool)
     * @tparam T value type
     * @param varName uniform variable name
     * @param val value of that variable
     */
    template<typename T>
    void setUniformValue(const std::string &varName, T val) const;

    template<std::size_t C>
    void setVectorValue(const std::string &varName, const PointND<C> &value) const;

private:
    void useNoIncrement() const;

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
