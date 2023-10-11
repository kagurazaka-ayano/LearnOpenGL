/**
 * @parent include/OpenGL/managers
 * @file FileManager.h
 * @author ayano
 * @date 9/15/23
 * @brief file manager, provided a static FileManager class as file manipulation interface
*/

#ifndef OPENGL_FILEMANAGER_H
#define OPENGL_FILEMANAGER_H

#include <string>
#include <fstream>
#include <sys/stat.h>


class FileManager {
public:
    /**
    * @brief read a text file from given path
    * @param path file path
    * @return content of the file, string
    */
    static std::string readFileStr(const std::string& path);

    /**
     * @brief read binary data from given file
     * @param path file path
     * @return content of the file, in byte array
     * @remark you need to manage the memory manually since this method creates a heap ID
     */
    static char* readFileBin(const std::string& path);

    /**
     * @brief get image as byte array
     * @param path image path
     * @param width image width
     * @param height image height
     * @param channelCount image channel count
     * @return byte array of the byte array returned
     */
    static unsigned char * getImage(const std::string& path, int width, int height, int channelCount);

    /**
     * @brief free the image from memory
     * @param image image object you get from getImage
     */
    static void freeImage(unsigned char* image);

    /**
     * @brief write the given content to the given string file
     * @remark
     * @param path file path
     * @param content file content to write into the file
     * @remark this will override the original file content
     * @return true if write is successful, false otherwise
     */
    static bool writeFileStr(const std::string& path, const std::string& content);

    /**
     * @brief write the the give content to the given binary file
     * @param path file path
     * @param content file content to write into file
     * @remark this will override the original file content
     * @return true if write is successful, false otherwise
     */
    static bool writeFileBin(const std::string &path, const char *content, const long &size);

    /**
     * @brief return size of the file in byte
     * @param path file path
     * @return size of the file
     */
    static long long sizeOf(const std::string& path);

    FileManager(const FileManager&) = delete;
    FileManager& operator=(const FileManager&) = delete;

private:
    FileManager() = default;
};


#endif //OPENGL_FILEMANAGER_H
