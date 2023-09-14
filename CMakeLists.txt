cmake_minimum_required(VERSION 3.10)
project(OpenGL)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(INCLUDE_DIR dependencies/glfw/include dependencies/glad/include dependencies/spdlog/include include/OpenGL)
set(LIB_DIR dependencies/glfw/lib dependencies/spdlog/lib)

file(GLOB SRC "src/*.cpp" "src/3dObjects/*.cpp")

add_executable(${PROJECT_NAME} ${SRC} dependencies/glad/src/glad.c)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR})
target_link_directories(${PROJECT_NAME} PRIVATE ${LIB_DIR})

target_link_libraries(${PROJECT_NAME} libglfw.3.dylib)
