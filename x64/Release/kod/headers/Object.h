#pragma once
#include "texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader_s.h"
using namespace std;
class Object
{
public:
	virtual void draw(Shader *ourShader) {};
	glm::fvec3 pos;
	Texture* textura1;
	unsigned int VAO;
	unsigned int VBO, EBO;

};

class pabloBlock
{
public:
	bool candraw = 0;
	unsigned int VAO;
	glm::f32vec3 pos;
	unsigned int* tex1;
	unsigned int* tex2;
	unsigned int* tex3;
	int typ = 0;
	bool faces[6] = { 0,0,0,0,0,0 };
};
