#version 460 core
layout(points) in;
layout(triangle_strip,max_vertices =4) out;
out vec3 texCoord;

float cubeVertices6[6][20] = {
        {0, 0, 0,  0, 0,
         1, 0, 0,  1, 0,
         0,  1, 0,  0, 1,
         1,  1, 0,  1, 1,
        
        },

        {0, 0,  1,  1, 0,
         1, 0,  1,  0, 0,
         0,  1,  1,  1, 1,
         1,  1,  1,  0, 1,
        
        },

        {
        0,  1,  1, 0, 1,
        0,  1,  0,  1, 1,
        0, 0,  1,  0, 0,
        0, 0, 0,  1, 0,
        
        },

         {1,  1,  1,  1, 1,
         1,  1, 0,  0, 1,
         1, 0,  1,  1, 0,
         1, 0, 0,  0, 0,
         
         },

        {0, 0, 0,  0, 1,
         1, 0, 0,  1, 1,
         0, 0,  1,  0, 0,
         1, 0,  1,  1, 0,
        
        },

        {0,  1, 0,  1, 0,
         1,  1, 0,  0, 0,
         0,  1,  1,  1, 1,
         1,  1,  1,  0, 1,
        
        }
    };
in Data
{
	vec2 TexCoord;
} data_in[];
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
    mat4 matrix =projection*view*model ;
	for(int i =0;i<20;i+=5)
    {
    vec3 tPos ={gl_in[0].gl_Position.x+cubeVertices6[int(data_in[0].TexCoord.x)][i+0],gl_in[0].gl_Position.y+cubeVertices6[int(data_in[0].TexCoord.x)][i+1],gl_in[0].gl_Position.z+cubeVertices6[int(data_in[0].TexCoord.x)][i+2]};
    gl_Position = matrix* vec4(tPos,1.0f);
	texCoord = vec3(cubeVertices6[int(data_in[0].TexCoord.x)][i+3],cubeVertices6[int(data_in[0].TexCoord.x)][i+4],data_in[0].TexCoord.y);
	EmitVertex();
    }
        EndPrimitive();
}