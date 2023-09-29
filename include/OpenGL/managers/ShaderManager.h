/*
 * @parent: src/managers
 * @file: ShaderManager.h
 * @author: ayano
 * @date: 9/17/23
 * 
*/

#ifndef OPENGL_SHADERMANAGER_H
#define OPENGL_SHADERMANAGER_H

#include <string>
#include <unordered_map>
#include <mutex>
#include <memory>
#include <array>

#include <managers/FileManager.h>
#include <glObjects/Shader.h>
#include <spdlog/spdlog.h>
#include <glad/glad.h>
#include <utilities/utilities.h>
#include <utilities/SingletonAbstract.hpp>


class ShaderManager : public SingletonAbstract<ShaderManager>{
    friend class SingletonAbstract<ShaderManager>;

    ShaderManager() = default;

    static ShaderManager* instance;
    static std::mutex mutex;

    /**
     * predefined shader type reference, also the directory name
     * @remark the "program" parameter is reserved for shader program and must be the last element
     */
    const std::unordered_map<std::type_index, std::string> SHADER_TYPE_REF{
            {typeid(FragShader), "frag"},
            {typeid(VertShader), "vert"},
            {typeid(GeomShader), "geom"},
            {typeid(ShaderProgram), "program"}
    };
    const std::string SHADER_ROOT = "../src/shaders/";
    const std::unordered_map<std::type_index, int> SHADER_GL_ENUM = {
            {typeid(FragShader), GL_FRAGMENT_SHADER},
            {typeid(VertShader), GL_VERTEX_SHADER},
            {typeid(GeomShader), GL_GEOMETRY_SHADER},
            {typeid(ShaderProgram), -1}
    };

    /**
     * shader cache
     */
    std::unordered_map<std::string, BaseShader*> cacheName;

    /**
     * cache based on ID of shader, values are the name of the shader
     */
    std::unordered_map<unsigned int, std::string> cacheID;

    /**
     * @brief add the shader to the cache
     * @param name shader name in the file system, relative path to the root shader directory
     * @param shader shader ID
     */
    template<typename T>
    void cacheAdd(const std::string& name, BaseShader* shader);

    /**
     * @brief remove the entry from the cache
     * @param name shader name in the file system, relative path to the root shader directory
     */
    template<typename T>
    void cachePop(const std::string& name);

    /**
     * remove entry from cache based on shader ID
     * @param shaderID shader ID
     */
    void cachePop(const unsigned int& shaderID);

    /**
     * @brief fetch shader with given name from cache
     * @param name shader name in the file system
     * @return the shader ID found, nullptr otherwise
     */
    template<typename T>
    T* cacheFind(const std::string& name);

    /**
     * fetch shader with given shader id
     * @param shaderID shader id
     * @return the shader ID
     */
    template<typename T>
    T* cacheFind(const unsigned int& shaderID);

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

    /**
     * @brief check whether GLAD is included
     */
    static void checkGLState();

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
     * use cachePop instead
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
     * use cachePop instead
     */
    template<size_t C>
    ShaderProgram * getShaderProgram(const std::string& name, const std::array<BaseShader*, C>& shaders);
};

template<typename T>
void ShaderManager::cacheAdd(const std::string& name, BaseShader* shader) {
    isShader<T>();
    std::lock_guard<std::mutex> lock(mutex);
    cacheName.emplace(ShaderManager::SHADER_TYPE_REF.find(typeid(T))->second + "/" + name, shader);
    cacheID.emplace(shader->ID, shader->name);
}

template<typename T>
void ShaderManager::cachePop(const std::string &name) {
    isShader<T>();
    std::lock_guard<std::mutex> lock(mutex);
    auto shader = cacheName.find(ShaderManager::SHADER_TYPE_REF.find(typeid(T))->second + "/" + name);
    if (shader == cacheName.end()) return;
    delete shader->second;
    cacheName.erase(shader);
}

template<typename T>
std::string ShaderManager::getShaderCode(const std::string &name) {
    std::string suffix = ShaderManager::SHADER_TYPE_REF.find(typeid(T))->second;
    std::string path = ShaderManager::SHADER_ROOT + suffix + "/" + name + "." + suffix;
    return FileManager::readFileStr(path);
}

template<typename T>
bool ShaderManager::writeShaderCode(const std::string &name, const std::string &content) {
    std::string path = ShaderManager::SHADER_ROOT + ShaderManager::SHADER_TYPE_REF.find(typeid(T))->second + "/" + name;
    if(FileManager::writeFileStr(path, content)){
        cachePop<T>(name);
        return true;
    }
    return false;
}

template<size_t C>
ShaderProgram * ShaderManager::getShaderProgram(const std::string &name, const std::array<BaseShader *, C> &shaders) {
    checkGLState();
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
    if(cacheFind<ShaderProgram>(name) != nullptr) return cacheFind<ShaderProgram>(name);
    unsigned int program = glCreateProgram();
    for(auto i : shaders) {
        glAttachShader(program, i->ID);
    }
    glLinkProgram(program);
    std::string error = checkLinkSuccessful(program);
    if (error == "OK") {
        cacheAdd<ShaderProgram>(name, new ShaderProgram(program, name));
        return cacheFind<ShaderProgram>(name);
    }
    spdlog::error("shader program generation failed, message: {0}", error);
    return nullptr;
}

template<typename T>
void ShaderManager::isShader() {
    static_assert(std::is_base_of<BaseShader, T>::value, "T is not a shader or shader program!");
}

template<typename T>
T* ShaderManager::cacheFind(const std::string &name) {
    isShader<T>();
    std::lock_guard<std::mutex> lock(mutex);
    auto ans = cacheName.find(ShaderManager::SHADER_TYPE_REF.find(typeid(T))->second + "/" + name);
    return ans == cacheName.end() ? nullptr : dynamic_cast<T*>(ans->second);
}

template<typename T>
T* ShaderManager::cacheFind(const unsigned int &shaderID) {
    isShader<T>();
    std::lock_guard<std::mutex> lock(mutex);
    return cacheFind<T>(cacheID.find(shaderID)->second);
}

template<typename T>
T* ShaderManager::getShaderObject(const std::string &name) {
    checkGLState();
    if (cacheFind<T>(name) != nullptr){
        return cacheFind<T>(name);
    }
    unsigned int shader = glCreateShader(SHADER_GL_ENUM.find(typeid(T))->second);
    std::string code = getShaderCode<T>(name);
    const char* cstr = code.c_str();
    glShaderSource(shader, 1, &cstr, nullptr);
    glCompileShader(shader);
    std::string error = checkCompileSuccessful(shader);
    if (error == "OK") {
        cacheAdd<T>(name, new T(shader, name));
        return cacheFind<T>(name);
    }
    spdlog::error("Vertex shader \"{1}\" creation failed, message: {0}", error, name);
    return nullptr;
}



#endif //OPENGL_SHADERMANAGER_H
