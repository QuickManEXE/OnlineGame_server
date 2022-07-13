#include "CUI.h"
#include "../System/TaskManager.h"

CUI::CUI():Task(eId_HUD,eUp_HUD,eRd_HUD),
m_font_big("ＭＳゴシック",128),
m_font_small("ＭＳゴシック", 32)
{

}

CUI::~CUI()
{
}

void CUI::Update()
{

}

void CUI::Render()
{
	auto list = TaskManager::GetInstance()->GetTasks(eId_Enemy);
	auto player = TaskManager::GetInstance()->GetTask(eId_Player);
	if(list.size()==0) m_font_big.Draw(128,128,1,1,1,"ゲームクリアー");	
	else if (!player) m_font_big.Draw(128, 128, 1, 1, 1, "ゲームオーバー");
}



