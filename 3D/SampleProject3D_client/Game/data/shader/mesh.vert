#version 430

uniform mat4 WorldMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 ShadowTextureMatrix;
layout (location = 0) in vec3	Vertex;
layout (location = 1) in vec3	Normal;
layout (location = 2) in vec2	TexCoord;
//フラグメントシェーダーに渡す変数
out vec3 V;//座標
out vec3 N;//法線ベクトル
out vec2 texCoord;
out vec4 vShadowCoord;    //!< シャドウデプスマップの参照用座標
void main(void)
{
	V=vec3(WorldMatrix * vec4(Vertex,1));
    gl_Position = ProjectionMatrix * ModelViewMatrix * vec4(Vertex,1);
    N = normalize(mat3(WorldMatrix)* Normal);
	vShadowCoord = ShadowTextureMatrix*ModelViewMatrix*vec4(Vertex,1);    // 影用座標値(光源中心座標)
        
	texCoord = TexCoord;
}
