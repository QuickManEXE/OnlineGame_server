#version 430

uniform sampler2D tDiffuse;
in vec2 texCoord;
out vec4 out_color;
void main() {
	vec4 textureColor = texture2D(tDiffuse, vec2( texCoord.x,texCoord.y) );
    out_color = textureColor;
}
