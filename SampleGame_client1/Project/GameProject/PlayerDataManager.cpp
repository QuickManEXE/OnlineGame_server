#include "PlayerDataManager.h"
#include"Charactor\CPlayer.h"


void PlayerDataManager::UpdateMembersData(PlayerData _playerData)
{
	int id = _playerData.member_id;
	auto itr = m_members_data.find(id);
	if (itr != m_members_data.end()) {

		auto data = m_members_data[id];
		data.playerData = _playerData;
		(*data.pointer->m_playerData) = _playerData;
	}
	else {
		//�V�����G���g���[����
		printf("ID[%d]���G���g���[���܂���\n", id);
		MemberData* member_data = &m_members_data[id];
		member_data->pointer = new CPlayer(id, CVector2D(0, 660),&member_data->playerData);
		member_data->playerData = _playerData;
		//m_members_data[id] = member_data;
	}
}

std::map<int, PlayerDataManager::MemberData> PlayerDataManager::GetMembersData()
{
	return m_members_data;
}


