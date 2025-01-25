#ifndef GLFWLEARN_C_TEXTURE_H
#define GLFWLEARN_C_TEXTURE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "iostream"
#include <experimental/filesystem>

//#include "../libraries/stb/stb_image.h"


class c_Texture {
private:
    unsigned int ID;
    std::string FilePath;
    unsigned char *LocalBuffer;
    int Width, Height, BPP;
public:
    c_Texture(const std::string &path);
    ~c_Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind();

    inline int GetWidth() const {return Width; }
    inline int GetHeight() const {return Height; }

};


#endif
