/**
 * @parent include/OpenGL/managers
 * @file ShaderManager.h
 * @author ayano
 * @date 9/17/23
 * 
*/

#ifndef OPENGL_SHADERMANAGER_H
#define OPENGL_SHADERMANAGER_H

#include <string>
#include <unordered_map>
#include <mutex>
#include <memory>
#include <array>

#include "managers/FileManager.h"
#include "glObjects/Shader.h"
#include "spdlog/spdlog.h"
#include "glad/glad.h"
#include "utilities/utilities.h"
#include "utilities/SingletonAbstract.hpp"
#include "utilities/PoolAbstract.h"


class ShaderManager : public SingletonAbstract<ShaderManager>, public PoolAbstract<BaseShader>{
    friend class SingletonAbstract<ShaderManager>;

    ShaderManager() = default;

    /**
     * predefined shader type reference, also the directory name
     * @remark the "program" parameter is reserved for shader program and must be the last element
     */
    static const std::unordered_map<std::type_index, std::string> SHADER_TYPE_REF;
    static const std::string SHADER_ROOT;
    static const std::unordered_map<std::type_index, int> SHADER_GL_ENUM;

    /**
     * check weather the shader complication is successful
     * @param shader shader id
     * @return "OK" if it's successful, error message otherwise
     */
    static std::string checkCompileSuccessful(const unsigned int& shader);

    /**
     * @brief check whether the program is linked successful
     * @param program shader program id
     * @return "OK" if it's successful, error message otherwise
     */
    static std::string checkLinkSuccessful(const unsigned int& program);

    template<typename T>
    static std::string getShaderName(const std::string& name);


    template<typename T>
    static void isShader();


public:
    void operator=(const ShaderManager&) = delete;
    ShaderManager(ShaderManager& other) = delete;

    /**
     * @brief get shader code from the file system
     * @param type shader type
     * @param name relative path to the root folder of this type of shader, with no suffix
     * @return the shader code
     */
    template<typename T>
    std::string getShaderCode(const std::string& name = "default");

    /**
     * @brief write shader code to a file
     * @param type shader type
     * @param name  relative path to the root folder of this type of shader
     * @param content shader code
     * @return true of write successful, false otherwise
     * @remark this will also remove the shader from the cache and recycle the memory, so the variables storing the pointer
     * pointing to this shader will be invalid after this function call
     */
    template<typename T>
    bool writeShaderCode(const std::string& name, const std::string& content);

    /**
     * generic way of getting a shader object
     * @tparam T type of shader object you wish to get
     * @param name name of the shader, corresponding to the relative path of the shader root folder
     * @return constructed shader object
     * @remark if the shader is already in the cache, it will return the cached shader object
     * @remark ShaderManager will handle all the garbage collections so DO NOT MANUALLY DELETE THE POINTER USING DELETE,
     * ref cachePop instead
     */
    template<typename T>
    T* getShaderObject(const std::string& name = "default");

    /**
     * generate a shader program with the given shaders
     * @tparam C count of shader you wish to put in
     * @param name name of the program
     * @return pointer pointing to the shader program object
     * @remark if the program is already in the cache, it will return the cached program object
     * @remark ShaderManager will handle all the garbage collections so DO NOT MANUALLY DELETE THE POINTER USING DELETE,
     * ref cachePop instead
     */
    template<size_t C>
    ShaderProgram * getShaderProgram(const std::string& name, const std::array<BaseShader*, C>& shaders);
};

template<typename T>
std::string ShaderManager::getShaderName(const std::string& name){
    return ShaderManager::SHADER_TYPE_REF.find(typeid(T))->second + "/" + name;
}

template<typename T>
std::string ShaderManager::getShaderCode(const std::string &name) {
    std::string suffix = ShaderManager::SHADER_TYPE_REF.find(typeid(T))->second;
    std::string path = ShaderManager::SHADER_ROOT + suffix + "/" + name + "." + suffix;
    return FileManager::readFileStr(path);
}

template<typename T>
bool ShaderManager::writeShaderCode(const std::string &name, const std::string &content) {
    std::string path = ShaderManager::SHADER_ROOT + ShaderManager::getShaderName<T>(name);
    if(FileManager::writeFileStr(path, content)){
        // pop because the shader was updated
        poolPop(name);
        return true;
    }
    return false;
}

template<size_t C>
ShaderProgram * ShaderManager::getShaderProgram(const std::string &name, const std::array<BaseShader *, C> &shaders) {
    checkGLState();
    if(poolRetrieve(name) != nullptr) return dynamic_cast<ShaderProgram *>(poolRetrieve(name));
    bool hasVertex = false, hasFragment = false;
    for (auto i: shaders) {
        if(dynamic_cast<FragShader*>(i) != nullptr) {
            hasFragment = true;
        }
        else if(dynamic_cast<VertShader*>(i) != nullptr){
            hasVertex = true;
        }
        if(hasVertex && hasFragment) break;
    }
    if (!hasVertex) spdlog::warn("Shader program {0} doesn't contain a vertex shader, this might result in errors", name);
    if (!hasFragment) spdlog::warn("Shader program {0} doesn't contain a fragment shader, this might result in errors", name);
    unsigned int program = glCreateProgram();
    for(auto i : shaders) {
        glAttachShader(program, i->ID);
    }
    glLinkProgram(program);
    std::string error = checkLinkSuccessful(program);
    if (error == "OK") {
        auto nameWithType = ShaderManager::getShaderName<ShaderProgram>(name);
        poolAdd(nameWithType, new ShaderProgram(program, nameWithType));
        return dynamic_cast<ShaderProgram *>(poolRetrieve(nameWithType));
    }
    spdlog::error("shader program generation failed, message: {0}", error);
    return nullptr;
}

template<typename T>
void ShaderManager::isShader() {
    static_assert(std::is_base_of<BaseShader, T>::value, "T is not a shader or shader program!");
}


template<typename T>
T* ShaderManager::getShaderObject(const std::string &name) {
    checkGLState();
    if (poolRetrieve(name) != nullptr){
        return dynamic_cast<T*>(poolRetrieve(name));
    }
    unsigned int shader = glCreateShader(SHADER_GL_ENUM.find(typeid(T))->second);
    std::string code = getShaderCode<T>(name);
    const char* cstr = code.c_str();
    glShaderSource(shader, 1, &cstr, nullptr);
    glCompileShader(shader);
    std::string error = checkCompileSuccessful(shader);
    if (error == "OK") {
        auto nameWithType = ShaderManager::getShaderName<T>(name);
        poolAdd(nameWithType, new T(shader, nameWithType));
        auto t = poolRetrieve(nameWithType);
        return dynamic_cast<T*>(t);
    }
    spdlog::error("Vertex shader \"{1}\" creation failed, message: {0}", error, name);
    return nullptr;
}




#endif //OPENGL_SHADERMANAGER_H
