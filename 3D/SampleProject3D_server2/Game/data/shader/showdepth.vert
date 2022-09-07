#version 430

layout (location = 0) in vec3 Vertex;

out vec2 texCoord;

void main(void)
{
  texCoord = Vertex.xy;
  gl_Position = vec4(Vertex.xy * 2.0 - 1.0, 0.0, 1.0);
}