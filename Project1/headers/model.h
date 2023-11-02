#pragma once
#include "Object.h"
#include "OBJ_Loader.h"
#include "shader_s.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "texture.h"
#include "vector"
class Model : public Object
{
public:
	std::vector<Texture*> textures;
	glm::vec3 scala;
    objl::Loader loader;
    	float angle;
	Model(const char* path, const char* path1,glm::vec3 scalar={1.f,1.f,1.f})
	{
		scala = scalar;
        Texture* texture1 = new Texture(path1);
		textures.push_back(texture1);
		loader.LoadFile(path);
        
        
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);

            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER,loader.LoadedVertices.size()*32, &loader.LoadedVertices[0], GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, loader.LoadedIndices.size()*4,&loader.LoadedIndices[0], GL_STATIC_DRAW);

            // position attribute
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            // color attribute
            // texture coord attribute
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
            glEnableVertexAttribArray(1);
        
	}
	void draw(Shader *ourShader)
	{
        glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model = glm::translate(model, pos);
        model = glm::scale(model, scala);
        model = glm::rotate(model, glm::radians(angle),glm::vec3(0,1,0));
        ourShader->setMat4("model", model);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, loader.LoadedIndices.size(), GL_UNSIGNED_INT, 0);
	}
};
