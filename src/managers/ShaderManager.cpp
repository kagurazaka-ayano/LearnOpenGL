/*
 * @parent: src/managers
 * @file: ShaderManager.cpp
 * @author: ayano
 * @date: 9/17/23
 * 
*/

#include "managers/ShaderManager.h"

ShaderManager* ShaderManager::instance = nullptr;
std::mutex ShaderManager::mutex;

ShaderManager *ShaderManager::Instance() {
    std::lock_guard<std::mutex> lock(mutex);
    if(instance == nullptr){
        instance = new ShaderManager();
    }
    return instance;
}

void ShaderManager::cacheAdd(const std::string& name, const SHADER_TYPE& type, const Shader& shader) {
    cache.emplace(ShaderManager::SHADER_TYPE_REF[static_cast<int>(type)] + "/" + name, shader);
}

void ShaderManager::cachePop(const std::string &name) {
    cache.erase(name);
}

std::string ShaderManager::getShaderCode(const ShaderManager::SHADER_TYPE &type, const std::string &name) {
    std::string suffix = ShaderManager::SHADER_TYPE_REF[static_cast<int>(type)];
    std::string path = ShaderManager::SHADER_ROOT + suffix + "/" + name + "." + suffix;
    return FileManager::readFileStr(path);
}

bool ShaderManager::writeShaderCode(const ShaderManager::SHADER_TYPE &type, const std::string &name, const std::string &content) {
    std::string path = ShaderManager::SHADER_ROOT + ShaderManager::SHADER_TYPE_REF[static_cast<int>(type)] + "/" + name;
    if(FileManager::writeFileStr(path, content)){
        cachePop(name);
        return true;
    }
    return false;
}

unsigned int ShaderManager::generateVertexObject(const std::string &name) {
    checkGLState();
    if (cache.find(name) != cache.end()){
        Shader& shader = cache.find(name)->second;
        return shader.object;
    }
    unsigned int shader = glCreateShader(GL_VERTEX_SHADER);
    std::string code = getShaderCode(SHADER_TYPE::VERT, name);
    const char* cstr = code.c_str();
    glShaderSource(shader, 1, &cstr, nullptr);
    glCompileShader(shader);
    std::string error = checkCompileSuccessful(shader);
    if (error == "OK") {
        cacheAdd(name, SHADER_TYPE::VERT, Shader(code,  shader));
        return shader;
    }
    spdlog::error("Vertex shader \"{1}\" creation failed, message: {0}", error, name);
    return -1;
}

unsigned int ShaderManager::generateFragmentObject(const std::string &name) {
    checkGLState();
    if (cache.find(name) != cache.end()){
        Shader& shader = cache.find(name)->second;
        return shader.object;
    }
    unsigned int shader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string code = getShaderCode(SHADER_TYPE::FRAG, name);
    const char* cstr = code.c_str();
    glShaderSource(shader, 1, &cstr, nullptr);
    glCompileShader(shader);
    std::string error = checkCompileSuccessful(shader);
    if (error == "OK") {
        cacheAdd(name, SHADER_TYPE::FRAG, Shader(code,  shader));
        return shader;
    }
    spdlog::error("Fragment shader \"{1}\" creation failed, message: {0}", error, name);
    return -1;
}

unsigned int ShaderManager::generateGeometryObject(const std::string &name) {
    checkGLState();
    if (cache.find(name) != cache.end()){
        Shader& shader = cache.find(name)->second;
        return shader.object;
    }
    unsigned int shader = glCreateShader(GL_GEOMETRY_SHADER);
    std::string code = getShaderCode(SHADER_TYPE::GEOM, name);
    const char* cstr = code.c_str();
    glShaderSource(shader, 1, &cstr, nullptr);
    glCompileShader(shader);
    std::string error = checkCompileSuccessful(shader);
    if (error == "OK") {
        cacheAdd(name, SHADER_TYPE::GEOM, Shader(code,  shader));
        return shader;
    }
    spdlog::error("Fragment shader \"{1}\" creation failed, message: {0}", error, name);
    return -1;
}

std::string ShaderManager::checkCompileSuccessful(const unsigned int &shader) {
    int success;
    char buffer[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success) return "OK";
    glGetShaderInfoLog(shader, 512, nullptr, buffer);
    return buffer;
}

void ShaderManager::checkGLState() {
    if (!glfwInit()) throw std::runtime_error("GLFW must be initialized in order to generate shader objects");
    if (glGetString == nullptr) throw std::runtime_error("GLAD must be initialized in order to generate shader objects");
}

std::string ShaderManager::checkLinkSuccessful(const unsigned int &program) {
    int success;
    char buffer[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (success) return "OK";
    glGetProgramInfoLog(program, 512, NULL, buffer);
    return buffer;
}

ShaderManager::Shader::Shader(std::string code, const unsigned int& object): code(std::move(code)), object(object){

}
