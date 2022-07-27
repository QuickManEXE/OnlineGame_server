#version 430
uniform mat4 PVWMatrix;
layout (location = 0) in vec3	Vertex;
void main(void)
{
	gl_Position = PVWMatrix *  vec4(Vertex,1);
}