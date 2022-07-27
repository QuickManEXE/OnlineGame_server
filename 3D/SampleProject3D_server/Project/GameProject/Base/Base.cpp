#include "Base.h"
std::list<Base*> Base::m_list;
Base::Base(int type) :m_kill(false), m_type(type) {
}
Base::~Base() {

}
void Base::SetKill() {
	//削除フラグON
	m_kill = true;
}
void Base::Update() {
}
void Base::Draw() {
}
void Base::HitCheck(Base* b) {
}

//★モデルのとの衝突判定
void Base::CollisionModel(CVector3D* pos, CVector3D* vec, float rad, CModel* model) {
	//モデルとの判定(球)
	//衝突データ格納用
	CCollTriangle out[256];
	//押し戻し量
	CVector3D v(0, 0, 0);
	//球とモデルとの衝突
	//エラーが出たら…１・読み込んでないない　２・コリジョンを設定していない
	int cnt = model->CollisionSphere(out, *pos + CVector3D(0, rad, 0), rad, 250);
	//接触した面の数繰り返す
	for (int i = 0; i < cnt; i++) {
		//接触した面が斜めより上を向いていたら地面
		if (out[i].m_normal.y > 0.5f) {
			//重力落下速度を0に戻す
			if (vec->y < 0) {
				vec->y = 0;
			}
		}
		//接触した面の方向へ、めり込んだ分押し戻す
		CVector3D nv = out[i].m_normal * (rad - out[i].m_dist);
		//最も大きな移動量を求める
		v.x = fabs(v.x) > fabs(nv.x) ? v.x : nv.x;
		v.y = fabs(v.y) > fabs(nv.y) ? v.y : nv.y;
		v.z = fabs(v.z) > fabs(nv.z) ? v.z : nv.z;
	}
	//押し戻す
	*pos += v;
	printf("c = %d\n", cnt);

}
bool Base::CollisionCapsuleToSphere(Base* b)
{
	return CCollision::CollisionCapsuleShpere(m_lineS, m_lineE, m_rad, b->m_pos, b->m_rad);
}
bool Base::CollisionSphereToCapsule(Base* b)
{
	return CCollision::CollisionCapsuleShpere(b->m_lineS, b->m_lineE, b->m_rad, m_pos, m_rad);
}
bool Base::CollisionCapsule(Base* b)
{
	
	return CCollision::CollisionCapsule(m_lineS, m_lineE, m_rad, b->m_lineS, b->m_lineE, b->m_rad);
}
bool Base::CollisionSphere(Base* b) {
	//球の衝突判定の実装

	return CCollision::CollisionShpere(m_pos,m_rad,b->m_pos,b->m_rad);
}

void Base::KillALL() {
	auto itr = m_list.begin();
	//末尾まで繰り返す
	while (itr != m_list.end()) {
		(*itr)->SetKill();
		itr++;
	}

}
void Base::CheckKillALL() {
	auto itr = m_list.begin();
	//末尾まで繰り返す
	while (itr != m_list.end()) {
		//削除チェック
		if ((*itr)->m_kill) {
			//削除
			delete* itr;
			//リストから除外する
			//次のオブジェクトを受け取る
			itr = m_list.erase(itr);
		}
		else {
			//次のオブジェクト
			itr++;
		}
	}

}
void Base::UpdateALL() {
	//イテレータ
	//http://vivi.dyndns.org/tech/cpp/iterator.html
	//先頭のオブジェクト
	//std::list<Base*>::iterator itr = m_list.begin();
	auto itr = m_list.begin();
	//末尾まで繰り返す
	while (itr != m_list.end()) {
		//更新
		(*itr)->Update();
		//次のオブジェクト
		itr++;
	}
}
void Base::DrawALL() {
	auto itr = m_list.begin();
	//末尾まで繰り返す
	while (itr != m_list.end()) {
		//更新
		(*itr)->Draw();
		//次のオブジェクト
		itr++;
	}

}

void Base::HitCheckALL() {
	auto itr = m_list.begin();
	//末尾まで繰り返す
	while (itr != m_list.end()) {
		auto ct = itr;
		ct++;
		while (ct != m_list.end()) {
			(*itr)->HitCheck(*ct);
			(*ct)->HitCheck(*itr);
			//次のオブジェクト
			ct++;
		}
		//次のオブジェクト
		itr++;
	}

}

void Base::Add(Base * b) {
	//
	auto itr = m_list.begin();
	//末尾まで繰り返す
	while (itr != m_list.end()) {
		if ((*itr)->GetType() > b->GetType()) {
			m_list.insert(itr, b);
			return;
		}
		//次のオブジェクト
		itr++;
	}
	m_list.push_back(b);

}



Base* Base::FindObject(int type) {
	//先頭から末尾まで繰り返す
	for (auto it = m_list.begin(); it != m_list.end(); ++it) {
		//オブジェクトのtypeが引数のtypeと一致すれば　そのオブジェクトを返す
		if ((*it)->GetType() == type) return (*it);
	}
	return nullptr;
}



