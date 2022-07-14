#include "CField.h"
//Taskのコンストラクタで
//ID、更新順序、描画順序を設定する
CField::CField(): Task(eId_Field,eUp_Field,eRd_Field)
{

}

void CField::Render()
{

}

void CField::CallCollision(Collision * c)
{
}
