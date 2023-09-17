/*
 * @parent: src/managers
 * @file: FileManager.cpp
 * @author: ayano
 * @date: 9/15/23
 * 
*/

#include <managers/FileManager.h>

std::mutex FileManager::mutex;
FileManager* FileManager::instance;

FileManager *FileManager::Instance() {
    std::lock_guard<std::mutex> lock(mutex);
    if(instance == nullptr){
        instance = new FileManager();
    }
    return instance;
}

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
    return ans;
}

bool FileManager::writeFileStr(const std::string &path, const std::string &content) {
    auto ofs = std::ofstream(path);
    if(!ofs.is_open()) return false;
    ofs << content;
    return true;
}

bool FileManager::writeFileBin(const std::string &path, const char *content, const long &size) {
    auto ofs = std::ofstream(path, std::ofstream::binary);
    if(!ofs.is_open()) return false;
    ofs.write(content, size);
    return false;
}

long long FileManager::sizeOf(const std::string &path) {
    struct stat buf{};
    if(stat(path.c_str(), &buf) != -1) return buf.st_size;
    return -1;
}




