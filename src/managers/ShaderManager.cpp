/*
 * @parent: src/managers
 * @file: ShaderManager.cpp
 * @author: ayano
 * @date: 9/17/23
 * 
*/

#include "managers/ShaderManager.h"

const auto ShaderManager::SHADER_TYPE_REF = std::unordered_map<std::type_index, std::string>{
        {typeid(FragShader), "frag"},
        {typeid(VertShader), "vert"},
        {typeid(GeomShader), "geom"},
        {typeid(ShaderProgram), "program"}
};

const auto ShaderManager::SHADER_GL_ENUM = std::unordered_map<std::type_index, int>{
        {typeid(FragShader), GL_FRAGMENT_SHADER},
        {typeid(VertShader), GL_VERTEX_SHADER},
        {typeid(GeomShader), GL_GEOMETRY_SHADER},
        {typeid(ShaderProgram), -1}
};

const std::string ShaderManager::SHADER_ROOT = "../src/shaders/";


std::string ShaderManager::checkCompileSuccessful(const unsigned int &shader) {
    int success;
    char buffer[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success) return "OK";
    glGetShaderInfoLog(shader, 512, nullptr, buffer);
    return buffer;
}

std::string ShaderManager::checkLinkSuccessful(const unsigned int &program) {
    int success;
    char buffer[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (success) return "OK";
    glGetProgramInfoLog(program, 512, nullptr, buffer);
    return buffer;
}


