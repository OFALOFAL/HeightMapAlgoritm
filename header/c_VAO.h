#ifndef GLFWLEARN_C_VAO_H
#define GLFWLEARN_C_VAO_H

#include <glad/glad.h>
#include "c_VBO.h"

class c_VAO {
public:
    // ID reference for the Vertex Array Object
    GLuint ID;
    // Constructor that generates a VAO ID
    c_VAO();

    // Links a VBO to the VAO using a certain layout
    void LinkAtrib(c_VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void *offset);
    // Binds the VAO
    void Bind();
    // Unbinds the VAO
    void Unbind();
    // Deletes the VAO
    void Delete();
};
#endif
