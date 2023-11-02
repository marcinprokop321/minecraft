#version 460 core
out vec4 FragColor;
in vec2 TexCoord;
in vec3 Collections;
// texture samplers
uniform sampler2D Texs;
void main()
{
		FragColor = mix(Col,texture(Texs,vec2(TexCoord.x,TexCoord.y)),0.5);
}