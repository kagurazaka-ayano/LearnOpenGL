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
#include <spdlog/spdlog.h>
#include <glad/glad.h>
#include <glfw/glfw3.h>

class ShaderManager {
public:
    /**
     * shader type enum
     */
    enum class SHADER_TYPE{
        FRAG,
        VERT,
        GEOM,
        PROGRAM
    };

private:
    ShaderManager() = default;
    ~ShaderManager() = default;

    static ShaderManager* instance;
    static std::mutex mutex;

    /**
     * predefined shader type reference, also the directory name
     * @remark the "program" parameter is reserved for shader program and must be the last element
     */
    const std::array<std::string, 4> SHADER_TYPE_REF{"frag", "vert", "geom", "program"};
    const std::string SHADER_ROOT = "../src/shaders/";

    /**
     * a shader class for internal use, will later implement reference counter
     */
    struct Shader{
        const std::string code;
        const unsigned int object;

        Shader(std::string code, const unsigned int& object);
    };

    /**
     * shader cache, not yet implemented cleaning the cache
     */
    std::unordered_map<std::string, Shader> cache;

    /**
     * @brief add the shader to the cache
     * @param name shader name in the file system, relative path to its
     * @param shader shader object
     */
    void cacheAdd(const std::string& name, const SHADER_TYPE& type, const Shader& shader);
    /**
     * @brief remove the entry from the cache
     * @param name shader name in the file system
     */
    void cachePop(const std::string& name);
    /**
     * check weather the shader complication is successful
     * @param shader shader id
     * @return "OK" if it's successful, error message otherwise
     */
    static std::string checkCompileSuccessful(const unsigned int& shader);

    static std::string checkLinkSuccessful(const unsigned int& program);

    static void checkGLState();

public:
    void operator=(const ShaderManager&) = delete;
    ShaderManager(ShaderManager& other) = delete;
    static ShaderManager* Instance();

    /**
     * @brief get shader code from the file system
     * @param type shader type
     * @param name relative path to the root folder of this type of shader, with no suffix
     * @return the shader code
     */
    std::string getShaderCode(const SHADER_TYPE& type, const std::string& name = "default");

    /**
     * @brief write shader code to a file
     * @param type shader type
     * @param name  relative path to the root folder of this type of shader
     * @param content shader code
     * @return true of write successful, false otherwise
     */
    bool writeShaderCode(const SHADER_TYPE& type, const std::string& name, const std::string& content);

    /**
     * @brief generate vertex shader object
     * @param name path of shader relative to its root folder
     * @return generated shader id
     */
    unsigned int generateVertexObject(const std::string& name = "default");

    /**
     * @brief generate fragment shader object
     * @param name path of shader relative to its root folder
     * @return generated shader id
     */
    unsigned int generateFragmentObject(const std::string& name = "default");

    /**
     * @brief generate geometry shader object
     * @param name path of shader relative to its root folder
     * @return generated shader id
     */
    unsigned int generateGeometryObject(const std::string& name = "default");

    /**
     * @brief generate shader program with given shaders
     * @tparam C number of shader you apply to the program
     * @param name name of the program, only used in finding program in the cache
     * @param shaders shader ids
     * @return generated shader program
     */
    template<unsigned int C>
    unsigned int generateShaderProgram(const std::string& name, const std::array<unsigned int, C>& shaders);
};

template<unsigned int C>
unsigned int ShaderManager::generateShaderProgram(const std::string &name, const std::array<unsigned int, C> &shaders) {
    checkGLState();
    unsigned int program = glCreateProgram();
    for(unsigned int i : shaders) {
        spdlog::info(i);
        glAttachShader(program, i);
    }
    glLinkProgram(program);
    std::string error = checkLinkSuccessful(program);
    spdlog::info(error);
    if (error == "OK") {
        cacheAdd(name, SHADER_TYPE::PROGRAM, Shader("", program));
        return program;
    }
    spdlog::error("shader program generation failed, message: {0}", error);
    return -1;
}

#endif //OPENGL_SHADERMANAGER_H
