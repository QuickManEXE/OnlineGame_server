#pragma once
#include"stdafx.h"
#include"Singleton\Singleton.h"

class CPlayer;

class PlayerDataManager : public Singleton<PlayerDataManager>{
public:
	struct PlayerData {
		int member_id;
		CVector2D pos;
		CVector2D vec;
		int key[CInput::eKeyMax]{ 0 };
	};
	struct MemberData {
		CPlayer* pointer;
		PlayerData playerData;
	};
public:
	std::map<int, MemberData> m_members_data;
public:
	void UpdateMembersData(PlayerData _playerData);
	std::map<int, PlayerDataManager::MemberData> GetMembersData();
	void RecieveMembersData();
};