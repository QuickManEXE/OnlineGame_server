#version 430
uniform vec4 Color;
in vec2 texCoord;
uniform sampler2D sampler;
out vec4 out_color;
void main() {
 
	vec4 texColor=vec4(1,1,1,1);
    texColor = texture2D(sampler, texCoord);
	out_color= texColor * Color;
}
