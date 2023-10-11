/**
 * @parent include/OpenGL/utilities
 * @file PoolAbstract.h
 * @author ayano
 * @date 10/1/23
 *
*/

#ifndef OPENGL_POOLABSTRACT_H
#define OPENGL_POOLABSTRACT_H
#include <unordered_map>
#include <string>
#include <mutex>
#include "utilities/utilities.h"

/**
 * interface for an object that can be put into the PoolAbstract
 */
class IPoolable{
public:
    IPoolable(unsigned int ID, std::string name);
    const unsigned int ID;
    const std::string name;
};


/**
 * @brief Object pool abstract, let the manager class publicly inherit this class to implement object pool support
 * @tparam T type of the object the manager is managing
 * @remark This should only be inherited by the manager class that controls the life cycle of the object
 */
template<typename T>
requires std::is_base_of<IPoolable, T>::value
class PoolAbstract {
public:
    /**
     * @brief add a entry to the pool
     * @param name name of the object
     * @param object pointer to the object allocated in the heap
     * @remark when the object is added to the pool, the pool will automatically increment its refCount by 1
     */
    void poolAdd(const std::string& name, T* object);
    /**
     * @brief remove an entry from the pool by its and free its memory
     * @param name name of the entry
     */
    void poolPop(const std::string& name);
    /**
     * @brief remove an entry from the pool by its and free its memory
     * @param id id of the entry
     */
    void poolPop(unsigned int id);
    /**
     * @brief retrieve an entry from the pool by its id
     * @param id id of the entry
     * @return pointer pointing to that entry on heap
     * @remark DON'T MANUALLY FREE THIS MEMORY, USE poolPop INSTEAD!
     */
    T* poolRetrieve(unsigned int id);
    /**
     * @brief retrieve an entry from the pool by its name
     * @param name name of the entry
     * @return pointer pointing to that entry on heap
     * @remark DON'T MANUALLY FREE THIS MEMORY, USE poolPop INSTEAD!
     */
    T* poolRetrieve(const std::string& name);

    /**
     * @brief trigger manual gc, collect all objects with refCount == 0
     * @return count of element collected
     */
    int collect();

protected:
    /**
     * pool element stored by (id -> obj) and (name -> id), for accessing by both name and id with O(1) speed
     */
    std::unordered_map<unsigned int, T*> poolID = std::unordered_map<unsigned int, T*>();
    std::unordered_map<std::string, unsigned int> poolName = std::unordered_map<std::string, unsigned int>();
private:
    static std::recursive_mutex poolMutex;
};

template<typename T>
requires std::is_base_of<IPoolable, T>::value
int PoolAbstract<T>::collect() {
    int ans = 0;
    for (const auto& i: poolID) {
        if (i.second->refCount == 0) poolPop(i.second);
        ans++;
    }
    return ans;
}



template<typename T>
requires std::is_base_of<IPoolable, T>::value
T *PoolAbstract<T>::poolRetrieve(const std::string &name) {
    std::lock_guard<std::recursive_mutex> lock(poolMutex);
    return poolName.find(name) != poolName.end() ? poolRetrieve(poolName.find(name)->second) : nullptr;
}

template<typename T>
requires std::is_base_of<IPoolable, T>::value
T *PoolAbstract<T>::poolRetrieve(unsigned int id) {
    std::lock_guard<std::recursive_mutex> lock(poolMutex);
    return poolID.find(id) != poolID.end() ? poolID.find(id)->second : nullptr;
}

template<typename T>
requires std::is_base_of<IPoolable, T>::value
void PoolAbstract<T>::poolPop(const std::string &name) {
    std::lock_guard<std::recursive_mutex> lock(poolMutex);
    if (poolName.find(name) == poolName.end()) {
        spdlog::error("Name {0} not found in pool!", name);
        return;
    }
    poolPop(name);
}

template<typename T>
requires std::is_base_of<IPoolable, T>::value
void PoolAbstract<T>::poolPop(unsigned int id) {
    std::lock_guard<std::recursive_mutex> lock(poolMutex);
    if(poolID.find(id) == poolID.end()){
        spdlog::error("ID {0} not found in pool!", id);
        return;
    }
    auto name = poolID.find(id)->second;
    poolID.erase(id);
    delete poolName.find(name)->second;
    poolName.erase(name);
}

template<typename T>
requires std::is_base_of<IPoolable, T>::value
void PoolAbstract<T>::poolAdd(const std::string& name, T *object) {
    std::lock_guard<std::recursive_mutex> lock(poolMutex);
    poolID.emplace(object->ID, object);
    poolName.emplace(name, object->ID);
}

template<typename T>
requires std::is_base_of<IPoolable, T>::value
std::recursive_mutex PoolAbstract<T>::poolMutex = std::recursive_mutex();


#endif //OPENGL_POOLABSTRACT_H
