#include"../header/c_VBO.h"

// Constructor that generates a Vertex Buffer Object and links it to vertices
c_VBO::c_VBO(GLfloat* vertices, GLsizeiptr size)
{
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_DYNAMIC_DRAW);
}

// Binds the VBO
void c_VBO::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

// Unbinds the VBO
void c_VBO::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Deletes the VBO
void c_VBO::Delete()
{
    glDeleteBuffers(1, &ID);
}