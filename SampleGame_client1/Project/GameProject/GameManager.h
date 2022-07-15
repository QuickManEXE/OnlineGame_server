#pragma once
#include "stdafx.h"
#include "System/Task.h"


class GameManager : public Task {
public:
	GameManager();
	~GameManager();

	void Update();
	void Render();
};