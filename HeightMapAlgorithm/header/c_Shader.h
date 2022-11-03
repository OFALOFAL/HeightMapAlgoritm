#ifndef GLFWLEARN_C_SHADER_H
#define GLFWLEARN_C_SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char* filename);

class c_Shader {
public:
    GLuint ID;

public:
    c_Shader(const char* vertexFile, const char* fragmentFile);

    void Activate();
    void Delete();
};


#endif //GLFWLEARN_C_SHADER_H
