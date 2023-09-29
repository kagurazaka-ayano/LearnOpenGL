/*
 * @parent: include/OpenGL/utilities
 * @file: SingletonAbstract.hpp
 * @author: ayano
 * @date: 9/24/23
 *
 *
 *
 *
*/

#ifndef OPENGL_SingletonAbstract_H
#define OPENGL_SingletonAbstract_H

#include <mutex>
/**
 * @brief let a class inherit this to be a singleton
 * @remark you still have to make the constructor of the class inheriting this class private, deleting the copy
 * constructor and the equal sign, and make T a friend of SingletonAbstract<T>, this class only help declared
 * the functions necessary for a singleton
 * @tparam T type of the derived class
 */
template<typename T>
class SingletonAbstract {
private:
    static std::mutex mutex;
    static std::unique_ptr<T> instance;
protected:
    SingletonAbstract() = default;
    virtual ~SingletonAbstract() = default;
public:
    void operator=(const SingletonAbstract& other) = delete;
    SingletonAbstract(SingletonAbstract& other) = delete;
    static T* Instance();
};

template<typename T>
T* SingletonAbstract<T>::Instance(){
    std::lock_guard<std::mutex> lock(mutex);
    if (instance == nullptr){
        instance.reset(new T);
    }
    return instance.get();
}

template<typename T>
std::mutex SingletonAbstract<T>::mutex;

template<typename T>
std::unique_ptr<T> SingletonAbstract<T>::instance = nullptr;

#endif //OPENGL_SingletonAbstract_H
