#include "Texture.hpp"
#include "../glad/glad.h"
#include "../stb_image.h"

#include <iostream>

Texture::Texture(const char *path, int format, int wrapMode, int filterMode)
{
    stbi_set_flip_vertically_on_load(true); 
    unsigned char *data = stbi_load(path, &this->width, &this->height, &this->channels, 0);

    if(data){
        glGenTextures(1, &this->ID);

        glBindTexture(GL_TEXTURE_2D, this->ID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMode);

        glTexImage2D(
            GL_TEXTURE_2D, // Texture Target
            0, // Mipmap Level
            format, // Texture Format
            this->width,
            this->height,
            0, //Border - always zero
            format, // Data format
            GL_UNSIGNED_BYTE, //data type
            data
        );

        glGenerateMipmap(GL_TEXTURE_2D);
    }else{
        std::cout << "Failed to load Texture `" << path << "`" << std::endl;
    }


    stbi_image_free(data);
}

Texture::~Texture()
{
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, this->ID);
}
