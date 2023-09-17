/*
 * @parent: src/test
 * @file: main.cpp
 * @author: ayano
 * @date: 9/16/23
 * 
*/

#include <mathObjects/PointND.h>
#include <managers/FileManager.h>
#include <iostream>

int main(){
    FileManager::writeFileStr("../src/shaders/frag/default.frag", "test");
    return 0;
}
