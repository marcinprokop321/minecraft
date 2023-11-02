#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 0) in vec3 aCol;
layout (location = 1) in vec2 aTexCoord;
out vec2 TexCoord;
out vec3 Col;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
	gl_Position = model*view*projection*vec4(aPos, 1.0f);
	TexCoord = aTexCoord;
	Col = aCol;
}