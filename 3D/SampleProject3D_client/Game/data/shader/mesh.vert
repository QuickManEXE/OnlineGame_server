#version 430

uniform mat4 WorldMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 ShadowTextureMatrix;
layout (location = 0) in vec3	Vertex;
layout (location = 1) in vec3	Normal;
layout (location = 2) in vec2	TexCoord;
//�t���O�����g�V�F�[�_�[�ɓn���ϐ�
out vec3 V;//���W
out vec3 N;//�@���x�N�g��
out vec2 texCoord;
out vec4 vShadowCoord;    //!< �V���h�E�f�v�X�}�b�v�̎Q�Ɨp���W
void main(void)
{
	V=vec3(WorldMatrix * vec4(Vertex,1));
    gl_Position = ProjectionMatrix * ModelViewMatrix * vec4(Vertex,1);
    N = normalize(mat3(WorldMatrix)* Normal);
	vShadowCoord = ShadowTextureMatrix*ModelViewMatrix*vec4(Vertex,1);    // �e�p���W�l(�������S���W)
        
	texCoord = TexCoord;
}
