#include "CEffect.h"

CEffect::CEffect(CVector2D &p):
Task(eId_Effect,eUp_Effect,eRd_Effect){
	img = COPY_RESOURCE("Effect_Bomb", CImage);
	img.SetCenter(48,48);
	pos = p;
	img.ChangeAnimation(0,false);

}
CEffect::~CEffect() {

}
void CEffect::Update() {
	img.UpdateAnimation();
	if (img.CheckAnimationEnd()) {
		SetKill();
	}
}
void CEffect::Render() {
	img.SetPos(pos);
	img.Draw();
}