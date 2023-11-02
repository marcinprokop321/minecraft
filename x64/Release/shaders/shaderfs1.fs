#version 460 core
out vec4 FragColor;
in vec2 TexCoord;
// texture samplers
uniform sampler2D Texs;
void main()
{
		FragColor = texture(Texs,vec2(TexCoord.x,TexCoord.y));
}