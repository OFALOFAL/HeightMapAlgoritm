cmake_minimum_required(VERSION 3.22)
project(HeightMapAlgorithm)

set(CMAKE_CXX_STANDARD 23)

# Disable GLFW extras
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Add GLFW subdirectory
add_subdirectory(libraries/glfw-3.4)

# Find OpenGL package
find_package(OpenGL REQUIRED)

add_definitions(-DGLM_ENABLE_EXPERIMENTAL)

# Add the executable
add_executable(
        HeightMapAlgorithm
        libraries/glad/src/glad.c
        src/main.cpp
        src/c_Shader.cpp
        header/c_Shader.h
        src/c_VBO.cpp
        header/c_VBO.h
        src/c_EBO.cpp
        header/c_EBO.h
        src/c_VAO.cpp
        header/c_VAO.h
        src/c_Texture.cpp
        header/c_Texture.h
        src/c_Camera.cpp
        header/c_Camera.h
        src/yAxisAlg.cpp
        header/yAxisAlg.h
        src/stb_image_implementation.cpp
)


# Set include directories for the target
target_include_directories(HeightMapAlgorithm PRIVATE
        libraries/glad/include
        libraries/glm
        libraries/stb
)

# Link libraries
target_link_libraries(HeightMapAlgorithm PRIVATE glfw OpenGL::GL stdc++fs)
