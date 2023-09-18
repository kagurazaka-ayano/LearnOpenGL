cmake_minimum_required(VERSION 3.10)
project(OpenGL)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(INCLUDE_DIR dependencies/glfw/include dependencies/glad/include dependencies/spdlog/include)
set(LIB_DIR dependencies/glfw/lib dependencies/spdlog/lib)

file(GLOB SRC "src/mathObjects/*.cpp" "src/managers/*.cpp")
file(GLOB MAIN "src/main/*.cpp")
file(GLOB TEST "src/test/*.cpp")



add_executable(${PROJECT_NAME} ${SRC} ${MAIN} dependencies/glad/src/glad.c)

add_executable(${PROJECT_NAME}_test ${SRC} ${TEST} dependencies/glad/src/glad.c)

target_link_directories(${PROJECT_NAME} PRIVATE ${LIB_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE libglfw.3.dylib)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR} include/OpenGL)

target_link_directories(${PROJECT_NAME}_test PRIVATE ${LIB_DIR})

target_link_libraries(${PROJECT_NAME}_test PRIVATE libglfw.3.dylib)

target_include_directories(${PROJECT_NAME}_test PRIVATE ${INCLUDE_DIR} include/OpenGL)




