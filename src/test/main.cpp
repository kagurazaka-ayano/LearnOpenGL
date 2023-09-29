/*
 * @parent: src/test
 * @file: main.cpp
 * @author: ayano
 * @date: 9/16/23
 * 
*/

#include <mathObjects/Color.h>
#include <unordered_map>
#include <iostream>
#include <typeindex>


int main(){
    auto pt = PointND<3>{1, 1, 34};
    std::cout << static_cast<std::string>(pt);

    return 0;
}
