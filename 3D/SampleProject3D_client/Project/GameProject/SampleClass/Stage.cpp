#include "Stage.h"
#include "../GID.h"
//コンストラクタ　オブジェクト生成時に呼ばれる
//　　　　　　　　　　　　　　　　　　　　基底クラス（Base）へ種類の情報を渡す
Stage::Stage():Base(eId_Field) {
	//座標の設定
	m_pos = CVector3D(0,0,0);

	//ADD_RESOURCE("Field", CModel::CreateModel("Field/Land/land.field"));
	
	//ADD_RESOURCE("Stage", CModel::CreateModel("Field/Dungeon/Dungeon.obj"));
	//ADD_RESOURCE("StageC", CModel::CreateModel("Field/Dungeon/DungeonC.obj",8,4,8));
	//キャラクター初期位置(-6337 * s, 1764 * s,-2103 * s)
	
	//フィールドモデル
	/*
	m_model_field = GET_RESOURCE("Field", CModelField);
	m_model_field->SetScale(200, 200, 200);
	m_model_field->SetDrawLength(9000);
	*/

	//モデル設定(Dungeon)

	float s = 0.3;
	m_model = COPY_RESOURCE("Stage", CModelObj);
	m_model_collision = COPY_RESOURCE("StageC", CModelObj);
	m_model.SetScale(s, s, s);
	m_model.UpdateMatrix();
	//描画しないものはUpdateMatrixを呼んでおく
	m_model_collision.SetScale(s, s, s);
	m_model_collision.UpdateMatrix();
	


}
//更新処理
//Base::UpdateALL関数内で呼ばれている
void Stage::Update() {



}
//描画処理
//Base::DrawALL関数内で呼ばれている
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

