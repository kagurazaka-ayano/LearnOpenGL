/*
 * @parent: src/glObjects
 * @file: Shader.cpp
 * @author: ayano
 * @date: 9/20/23
 * 
*/

#include "glObjects/Shader.h"


FragShader::FragShader(const unsigned int &object, const std::string& name = "default") : BaseShader(name, object) {

}

VertShader::VertShader(const unsigned int &object, const std::string& name = "default") : BaseShader(name, object){

}

GeomShader::GeomShader(const unsigned int &object, const std::string& name = "default") : BaseShader(name, object) {

}

ShaderProgram::ShaderProgram(const unsigned int &object, const std::string& name = "default") : BaseShader(name, object){

}

void ShaderProgram::use() {
    refCount++;
    glUseProgram(ID);

}

void ShaderProgram::useNoIncrement() const {
    glUseProgram(ID);
}

template<std::size_t C>
void ShaderProgram::setVectorValue(const std::string &varName, const PointND<C> &value) const {
    static_assert(within(0, C, 4, false, true), "vector dimension must be in range [1, 4]!");
    int loc = glGetUniformLocation(ID, varName.c_str());
    if (loc == -1) spdlog::error("invalid uniform variable name {0}, not found in any of the shaders belong to the shader program {1}", varName, name);
    else {
        VEC_FUNC_REF[C - 1](loc, 1, value.coord.data());
        ShaderProgram::useNoIncrement();
    }
}

template<typename T>
constexpr void ShaderProgram::checkValidType() const {
    static_assert(STANDARD_FUNC_REF.contains(typeid(T)), "invalid uniform type!, must be int, float, bool or PointND(0 < N <= 4)");
}

template<typename T>
void ShaderProgram::setUniformValue(const std::string &varName, T val) const {
    checkValidType<T>();
    int loc = glGetUniformLocation(ID, varName.c_str());
    if (loc == -1) spdlog::error("invalid uniform variable name {0}, not found in any of the shaders belong to the shader program {1}", varName, name);
    else {

        glUniform1i(loc, val);
    }
}

BaseShader::BaseShader(std::string  name, unsigned int ID) : name(std::move(name)), ID(ID) {

}

void BaseShader::dispose() {
    refCount--;
}

BaseShader::~BaseShader() = default;



