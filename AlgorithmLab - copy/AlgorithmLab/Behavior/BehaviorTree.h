#ifndef BEHAVIOR_TREE_H_
#define BEHAVIOR_TREE_H_

#include <string>

class ActionBase;
class ExecJudgmentBase;
class NodeBase;
class BehaviorData;
class Enemy;

// �r�w�C�r�A�c���[
template<typename class T>
class BehaviorTree
{
public:
	// �I�����[��
	enum SELECT_RULE
	{
		NON,
		PRIORITY,			// �D�揇��
		SEQUENCE,			// �V�[�P���X
		SEQUENTIAL_LOOPING,	// �V�[�P���V�������[�s���O
		RANDOM,				// �����_��
		ON_OFF,				// �I���E�I�t
	};

public:
	BehaviorTree() :
		m_Root(NULL)
	{
	}

	// ���s�m�[�h�𐄘_����
	NodeBase *Inference(T *enemy, BehaviorData *data){
		// �f�[�^�����Z�b�g���ĊJ�n
		data->Init();
		return m_Root->Inference(enemy, data);
	}

	// �V�[�P���X�m�[�h���琄�_�J�n
	NodeBase *SequenceBack(NodeBase *sequence_node, T *enemy, BehaviorData *data) {
		return sequence_node->Inference(enemy, data);
	}
	
	// �m�[�h�ǉ�
	void AddNode(std::string search_name, std::string entry_name, int priority, SELECT_RULE select_rule, ExecJudgmentBase *judgment, ActionBase *action)
	{
		if (search_name != "")
		{
			NodeBase* search_node = m_Root->SearchNode(search_name);

			if (search_node != NULL)
			{
				NodeBase* sibling = search_node->GetLastChild();
				NodeBase* add_node = new NodeBase(entry_name, search_node, sibling, priority, select_rule, judgment, action, search_node->GetHirerchyNo() + 1);

				search_node->AddChild(add_node);
			}
		}
		else {
			if (m_Root == NULL)
			{
				m_Root = new NodeBase(entry_name, NULL, NULL, priority, select_rule, judgment, action, 1);
			}
			else {
				printf("���[�g�͊��ɓo�^����Ă��܂�\n");
			}
		}
	};

	// �c���[�\����\��
	void PrintTree()
	{
		if (m_Root != NULL)
		{
			m_Root->PrintName();
		}
	};

	// ���s
	NodeBase *Run(T *enemy, NodeBase *action_node, BehaviorData *data) {
		// �m�[�h���s
		ActionBase::STATE state = action_node->Run(enemy);

		// ����I��
		if (state == ActionBase::STATE::COMPLETE)
		{
			// �V�[�P���X�̓r�����𔻒f
			NodeBase* sequence_node = data->PopSequenceNode();

			// �r������Ȃ��Ȃ�I��
			if (sequence_node == NULL)
			{
				return NULL;
			}
			else {
				// �r���Ȃ炻������n�߂�
				return SequenceBack(sequence_node, enemy, data);
			}
			// ���s�͏I��
		}
		else if (state == ActionBase::STATE::FAILED) {
			return NULL;
		}

		// ����ێ�
		return action_node;
	}
	;
private:
	// ���[�g�m�[�h
	NodeBase *m_Root;
};

#endif
