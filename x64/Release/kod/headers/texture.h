#pragma once
#include "stb_image/stb_image.h"
#include <glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
class Texture
{
public:
	int width, height, nrChannels;
	unsigned int texture;
	unsigned char* data;
	Texture(const char* path1,int form=1)
	{
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        // set texture filtering parameters
        if (form)
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }
        else
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        }
        // load image, create texture and generate mipmaps
        stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
        unsigned char* data = stbi_load(path1, &width, &height, &nrChannels, 0);
        if (data)
        {
            if (nrChannels > 3)
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
        }
        stbi_image_free(data);
        glBindTexture(GL_TEXTURE_2D, 0);
	}
    void bind(int slot=0)
    {

        glActiveTexture(slot+GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
    }
};
class Texture3D
{
public:
    int width, height, nrChannels;
    unsigned int texture;
    Texture3D(std::string* path1,glm::vec3 pos, int form = 1)
    {
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D_ARRAY, texture);
        glPixelStorei(GL_UNPACK_ROW_LENGTH, pos.x);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);


        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);

        if (form)
        {
            glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }
        else
        {
            glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        }

        stbi_set_flip_vertically_on_load(true);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_LEVEL, pos.z);
        glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, pos.x, pos.y, pos.z, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
       for (int i = 0; i < pos.z; i++)
         {
           unsigned char* data = stbi_load(path1[i].c_str(), &width, &height, &nrChannels, 0);
           if (nrChannels > 3)
               glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, pos.x, pos.y, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);
           else
               glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, pos.x, pos.y, 1, GL_RGB, GL_UNSIGNED_BYTE, data);
           stbi_image_free(data);
         }
        
    }
    void bind(int slot = 0)
    {

        glActiveTexture(slot + GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D_ARRAY, texture);
    }
};

