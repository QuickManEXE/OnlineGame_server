#version 430
uniform mat4 PVWMatrix;
layout (location = 0) in vec3	Vertex;

layout (location = 2) in vec2	TexCoord;
out vec2 texCoord;
void main(void)
{
	gl_Position = PVWMatrix *  vec4(Vertex,1);
	texCoord = TexCoord;
}