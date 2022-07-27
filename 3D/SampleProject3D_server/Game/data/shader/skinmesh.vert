#version 430

uniform mat4 Transforms[180];
uniform mat4 WorldMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 ShadowTextureMatrix;
uniform int useSkin=0;

layout (location = 0) in vec3 Vertex;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 TexCoord;
layout (location = 3) in vec4 weights;
layout (location = 4) in vec4 indices;

//�t���O�����g�V�F�[�_�[�ɓn���ϐ�
out vec3 V;//���W
out vec3 N;//�@���x�N�g��
out vec2 texCoord;
out vec4 vShadowCoord;    //!< �V���h�E�f�v�X�}�b�v�̎Q�Ɨp���W
void main(void)
{

	if(useSkin==1) {
		mat4 comb = mat4(0);
		comb += Transforms[int(indices.x)] * weights.x;
		comb += Transforms[int(indices.y)] * weights.y;
		comb += Transforms[int(indices.z)] * weights.z;
		comb += Transforms[int(indices.w)] * weights.w;

		vec4 skinPosition = ModelViewMatrix * comb * vec4(Vertex,1);
		V = vec3(WorldMatrix * comb * vec4(Vertex,1));
		gl_Position = ProjectionMatrix * skinPosition;
		N = normalize(mat3(WorldMatrix* comb) * Normal);
	} else {
		V = vec3(WorldMatrix * vec4(Vertex,1));
		gl_Position = ProjectionMatrix * ModelViewMatrix * vec4(Vertex,1);
		N = normalize(mat3(WorldMatrix) * Normal);
	}
	
	vShadowCoord = ShadowTextureMatrix*ModelViewMatrix*vec4(Vertex,1);    // �e�p���W�l(�������S���W)
	texCoord = TexCoord;
}
