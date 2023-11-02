#version 460 core
out vec4 FragColor;
in vec3 texCoord;
uniform sampler2DArray Texs;
uniform vec3 watercolor;
void main()
{
    vec4 t = texture(Texs,texCoord);
    FragColor = vec4(mix(t.xyz,watercolor,0.5),t.a);
}