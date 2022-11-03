#ifndef GLFWLEARN_C_EBO_H
#define GLFWLEARN_C_EBO_H

#include <glad/glad.h>


class c_EBO {
public:
    // ID reference of Elements Buffer Object
    GLuint ID;
    // Constructor that generates a Elements Buffer Object and links it to indices
    c_EBO(GLuint* indices, GLsizeiptr size);

    // Binds the EBO
    void Bind();
    // Unbinds the EBO
    void Unbind();
    // Deletes the EBO
    void Delete();
};


#endif
