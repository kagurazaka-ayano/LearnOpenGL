/*
 * @parent: src/managers
 * @file: FileManager.cpp
 * @author: ayano
 * @date: 9/15/23
 * 
*/

#include "managers/FileManager.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

std::string FileManager::readFileStr(const std::string &path) {
    auto ifs{std::ifstream(path)};
    std::string ans, line;
    if(ifs.is_open()){
        while(getline(ifs, line)){
            ans += line + '\n';
        }
        ifs.close();
        return ans;
    }
    return "";
}

char *FileManager::readFileBin(const std::string &path) {
    long long size = sizeOf(path);
    if (size == -1) return nullptr;
    auto ifs = std::ifstream(path, std::ifstream::binary);
    char* ans = new char[size];
    ifs.read(ans, size);
    ifs.close();
    return ans;
}

bool FileManager::writeFileStr(const std::string &path, const std::string &content) {
    auto ofs = std::ofstream(path);
    if(!ofs.is_open()) return false;
    ofs << content;
    ofs.close();
    return true;
}

bool FileManager::writeFileBin(const std::string &path, const char *content, const long &size) {
    auto ofs = std::ofstream(path, std::ofstream::binary);
    if(!ofs.is_open()) return false;
    ofs.write(content, size);
    ofs.close();
    return true;
}

long long FileManager::sizeOf(const std::string &path) {
    struct stat buf{};
    if(stat(path.c_str(), &buf) != -1) return buf.st_size;
    return -1;
}

unsigned char *FileManager::getImage(const std::string &path, int width, int height, int channelCount) {
    return stbi_load(path.data(), &width, &height, &channelCount, 0);
}

void FileManager::freeImage(unsigned char* image) {
    stbi_image_free((void*)image);
}



