/*
 * @parent: src/managers
 * @file: FileManager.h
 * @author: ayano
 * @date: 9/15/23
 * 
*/

#ifndef OPENGL_FILEMANAGER_H
#define OPENGL_FILEMANAGER_H

#include <string>
#include <fstream>
#include <spdlog/spdlog.h>
#include <sys/stat.h>

class FileManager {
private:
    FileManager() = default;
    virtual ~FileManager() = default;

    static FileManager* instance;
    static std::mutex mutex;

public:

    FileManager(FileManager& other) = delete;
    void operator=(const FileManager&) = delete;

    static FileManager* Instance();


    /**
    * @brief read a text file from given path
    * @param path file path
    * @return content of the file, string
    */
    std::string readFileStr(const std::string& path);

    /**
     * @brief read binary data from given file
     * @param path file path
     * @return content of the file, in byte array
     * @remark you need to manage the memory manually since this method creates a heap object
     */
    char* readFileBin(const std::string& path);

    /**
     * @brief write the given content to the given string file
     * @remark
     * @param path file path
     * @param content file content to write into the file
     * @return true if write is successful, false otherwise
     */
    bool writeFileStr(const std::string& path, const std::string& content);

    /**
     * @brief write the the give contest to the given binary file
     * @param path file path
     * @param content file content to write into file
     * @return true if write is successful, false otherwise
     */
    bool writeFileBin(const std::string &path, const char *content, const long &size);

    /**
     * @brief return size of the file in byte
     * @param path file path
     * @return size of the file
     */
    static long long sizeOf(const std::string& path);
};


#endif //OPENGL_FILEMANAGER_H
