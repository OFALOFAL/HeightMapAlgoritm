#ifndef GLFWLEARN_C_VBO_H
#define GLFWLEARN_C_VBO_H

#include <glad/glad.h>


class c_VBO {
public:
    // Reference ID of the Vertex Buffer Object
    GLuint ID;
    // Constructor that generates a Vertex Buffer Object and links it to vertices
    c_VBO(GLfloat* vertices, GLsizeiptr size);

    // Binds the VBO
    void Bind();
    // Unbinds the VBO
    void Unbind();
    // Deletes the VBO
    void Delete();
};

#endif
