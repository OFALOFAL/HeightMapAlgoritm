#include"../header/c_VAO.h"

// Constructor that generates a VAO ID
c_VAO::c_VAO()
{
    glGenVertexArrays(1, &ID);
}

// Links a VBO to the VAO using a certain layout
void c_VAO::LinkAtrib(c_VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void *offset)
{
    VBO.Bind();
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    VBO.Unbind();
}

// Binds the VAO
void c_VAO::Bind()
{
    glBindVertexArray(ID);
}

// Unbinds the VAO
void c_VAO::Unbind()
{
    glBindVertexArray(0);
}

// Deletes the VAO
void c_VAO::Delete()
{
    glDeleteVertexArrays(1, &ID);
}