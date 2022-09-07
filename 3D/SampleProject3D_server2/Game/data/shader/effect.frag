#version 430

float rand(vec2 co) {
    float t = fract(co.x * 43758.5453);
    return t;
}
 
uniform sampler2D tDiffuse;
uniform vec2 vScreenSize;
in vec2 texCoord;
out vec4 out_color;

void main() {
 

    float radius = 5.0;
 
    float x = (texCoord.x * vScreenSize.x) + rand(vec2(texCoord.x,texCoord.y)) * radius * 2.0 - radius;
    float y = (texCoord.y * vScreenSize.y) + rand(vec2(texCoord.y,texCoord.x)) * radius * 2.0 - radius;
 
    vec4 textureColor = texture2D(tDiffuse, vec2( texCoord.x+ rand(vec2(texCoord.x,texCoord.y))*0.01,texCoord.y + rand(vec2(texCoord.y,texCoord.x))*0.01 ) );
    out_color = textureColor;
}
