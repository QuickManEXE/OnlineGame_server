#pragma once
#include "stdafx.h"
#include "System/Task.h"


class GameManager : public Task {
public:
	static int m_member_id;
public:
	GameManager();
	~GameManager();

	void Update();
	void Render();
};