/*
 * @parent: src
 * @file: utilities.cpp
 * @author: ayano
 * @date: 9/24/23
 * 
*/

#include "utilities/utilities.h"



void runtimeAssert(const std::unordered_map<bool, std::string>& expMap){
    for (const auto& i : expMap) runtimeAssert(i.first, i.second);
}
