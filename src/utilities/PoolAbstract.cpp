/*
 * @parent: src/utilities
 * @file: PoolAbstract.cpp
 * @author: ayano
 * @date: 10/10/23
 * 
*/

#include "utilities/PoolAbstract.h"

IPoolable::IPoolable(unsigned int ID, std::string name) : ID(ID), name(std::move(name)) {

}

