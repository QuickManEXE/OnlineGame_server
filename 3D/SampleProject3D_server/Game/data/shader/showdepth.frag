#version 430

uniform sampler2D depth;
 
const float dx = 0.000976562;
const float dy = 0.000976562;
in vec2 texCoord;
out vec4 out_color;

float peek(const in float x, const in float y)
{
  return texture2D(depth, vec2(x, y)).r;
}
 
void main (void)
{
  float x = texCoord.x;
  float y = texCoord.y;
  mat3 m = mat3(
    peek(x - dx, y - dy), peek(x, y - dy), peek(x + dx, y - dy),
    peek(x - dx, y     ), peek(x, y     ), peek(x + dx, y     ),
    peek(x - dx, y + dy), peek(x, y + dy), peek(x + dx, y + dy)
  );
  vec2 h = vec2(
    m[0][0] - m[0][2] + (m[1][0] - m[1][2]) * 2.0 + m[2][0] - m[2][2],
    m[0][0] - m[2][0] + (m[0][1] - m[2][1]) * 2.0 + m[0][2] - m[2][2]
  );  
  float d = step(0.99, 1.0 - length(h));
  out_color = vec4(vec3(d), 1.0-d);
}