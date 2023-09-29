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

std::string ShaderManager::checkCompileSuccessful(const unsigned int &shader) {
    int success;
    char buffer[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success) return "OK";
    glGetShaderInfoLog(shader, 512, nullptr, buffer);
    return buffer;
}

void ShaderManager::checkGLState() {
    if (glGetString == nullptr) throw std::runtime_error("GLAD must be initialized in order to generate shader objects");
}

std::string ShaderManager::checkLinkSuccessful(const unsigned int &program) {
    int success;
    char buffer[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (success) return "OK";
    glGetProgramInfoLog(program, 512, nullptr, buffer);
    return buffer;
}

void ShaderManager::cachePop(const unsigned int &shaderID) {
    std::lock_guard<std::mutex> lock(mutex);
    if(cacheID.find(shaderID) == cacheID.end()) return;
    auto shaderName = cacheID[shaderID];
    cacheID.erase(shaderID);
    cacheName.erase(shaderName);
}
