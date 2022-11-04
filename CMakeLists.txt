cmake_minimum_required(VERSION 3.22)
project(HeightMapAlgorithm)

set(CMAKE_CXX_STANDARD 23)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(libraries/glfw-3.3.8)

find_package(OpenGL REQUIRED)

link_libraries(stdc++fs)

add_executable(HeightMapAlgorithm libraries/glad/src/glad.c src/main.cpp src/c_Shader.cpp header/c_Shader.h src/c_VBO.cpp header/c_VBO.h src/c_EBO.cpp header/c_EBO.h src/c_VAO.cpp header/c_VAO.h libraries/stb/stb.cpp src/c_Texture.cpp header/c_Texture.h src/c_Camera.cpp header/c_Camera.h src/yAxisAlg.cpp src/yAxisAlg.cpp header/yAxisAlg.h)

include_directories(libraries/glad/include)
include_directories(libraries/glm/)

target_link_libraries(HeightMapAlgorithm libraries/glfw)
target_link_libraries(HeightMapAlgorithm OpenGL::GL)
