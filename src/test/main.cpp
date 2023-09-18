/*
 * @parent: src/test
 * @file: main.cpp
 * @author: ayano
 * @date: 9/16/23
 * 
*/

#include <mathObjects/PointND.h>
#include <managers/ShaderManager.h>
#include <iostream>

int main(){
    auto manager = ShaderManager::Instance();
    std::cout<<manager->generateFragmentObject();
    return 0;
}
