#pragma once
#include "../stdafx.h"
#include "../System/Task.h"
#include "../System/Collision.h"

class CUI : public Task{
private:
	CFont m_font_big;
	CFont m_font_small;

public:
	CUI();
	~CUI();

	void Update();
	void Render();

};