#include "fileManager.h"

/**
 * Get the content of a shader file with certain type and name
 * @param type type of the shader, used to determine which folder to look up
 * @param name name of the shader, with no suffix
 * @return content of the shader file, in string, empty in failure
 * @remark fill in only the type of the shader to get the default shader of this type
 * @remark MEMORY MUST BE MANUALLY RECYCLED
 */
std::string getShader(const SHADER_TYPE& type, const std::string& name){
    std::string ans, line, path = SHADER_ROOT + SHADER_TYPE_REF[static_cast<int>(type)] + "/" + name + "." + SHADER_TYPE_REF[static_cast<int>(type)];
    std::ifstream fileIn(path);
    if(fileIn.is_open()){
        while(getline(fileIn, line)){
            ans += line + '\n';
        }
        fileIn.close();
        return ans.c_str();
    }
    spdlog::warn("{0} shader \"{1}.{0}\" (inferred path: {2}) didn't load successfully", SHADER_TYPE_REF[static_cast<int>(type)], name, path);
    return "";
}

/**
 * Write a shader string to the given shader type and file
 * @param type SHADER_TYPE enum, indicating type of the shader
 * @param name name of the shader
 * @param content content of the new shader
 * @return true if the shader is successfully write to the file, false otherwise
 */
bool writeShader(const SHADER_TYPE& type, const std::string& name, const std::string& content){
    return false;
}
