#pragma once
#include "stdafx.h"
#include "System/Task.h"


class Game : public Task {
public:
	static int m_member_id;
public:
	Game();
	~Game();

	void Update();
	void Render();
};