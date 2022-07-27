#include "Stage.h"
#include "../GID.h"
//�R���X�g���N�^�@�I�u�W�F�N�g�������ɌĂ΂��
//�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@���N���X�iBase�j�֎�ނ̏���n��
Stage::Stage():Base(eId_Field) {
	//���W�̐ݒ�
	m_pos = CVector3D(0,0,0);

	//ADD_RESOURCE("Field", CModel::CreateModel("Field/Land/land.field"));
	
	//ADD_RESOURCE("Stage", CModel::CreateModel("Field/Dungeon/Dungeon.obj"));
	//ADD_RESOURCE("StageC", CModel::CreateModel("Field/Dungeon/DungeonC.obj",8,4,8));
	//�L�����N�^�[�����ʒu(-6337 * s, 1764 * s,-2103 * s)
	
	//�t�B�[���h���f��
	/*
	m_model_field = GET_RESOURCE("Field", CModelField);
	m_model_field->SetScale(200, 200, 200);
	m_model_field->SetDrawLength(9000);
	*/

	//���f���ݒ�(Dungeon)

	float s = 0.3;
	m_model = COPY_RESOURCE("Stage", CModelObj);
	m_model_collision = COPY_RESOURCE("StageC", CModelObj);
	m_model.SetScale(s, s, s);
	m_model.UpdateMatrix();
	//�`�悵�Ȃ����̂�UpdateMatrix���Ă�ł���
	m_model_collision.SetScale(s, s, s);
	m_model_collision.UpdateMatrix();
	


}
//�X�V����
//Base::UpdateALL�֐����ŌĂ΂�Ă���
void Stage::Update() {



}
//�`�揈��
//Base::DrawALL�֐����ŌĂ΂�Ă���
void Stage::Draw() {
	//m_model_field->Render();
	m_model.Render();

}
CModel* Stage::GetCollisionModel()
{
	//return &m_model;
	//return m_model_field;
	return &m_model_collision;
}

