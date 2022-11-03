#include "../header/c_Texture.h"

c_Texture::c_Texture(const std::string &path)
    : ID(0), FilePath(path), LocalBuffer(nullptr), Width(0), Height(0), BPP(0){

    stbi_set_flip_vertically_on_load(1);

    LocalBuffer = stbi_load(path.c_str(), &Width, &Height, &BPP, 4);

    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_READ_COLOR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_READ_COLOR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,Width, Height, 0/*BORDER*/, GL_RGBA, GL_UNSIGNED_BYTE, LocalBuffer);

    if (LocalBuffer){
        stbi_image_free(LocalBuffer);
    }

}

c_Texture::~c_Texture() {
    glDeleteTextures(1, &ID);
}

void c_Texture::Bind(unsigned int slot) const {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, ID);
}

void c_Texture::Unbind() {
    glBindTexture(GL_TEXTURE_2D,0);
}
