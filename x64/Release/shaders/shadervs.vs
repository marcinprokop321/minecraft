#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
out Data
{
	vec2 TexCoord;
} data_out;
void main()
{
	gl_Position =vec4(aPos, 1.0f);
	data_out.TexCoord = aTexCoord;
}