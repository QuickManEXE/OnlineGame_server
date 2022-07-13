#ifndef BEHAVIOR_TREE_H_
#define BEHAVIOR_TREE_H_

#include <string>

class ActionBase;
class ExecJudgmentBase;
class NodeBase;
class BehaviorData;
class Enemy;

// ビヘイビアツリー
template<typename class T>
class BehaviorTree
{
public:
	// 選択ルール
	enum SELECT_RULE
	{
		NON,
		PRIORITY,			// 優先順位
		SEQUENCE,			// シーケンス
		SEQUENTIAL_LOOPING,	// シーケンシャルルーピング
		RANDOM,				// ランダム
		ON_OFF,				// オン・オフ
	};

public:
	BehaviorTree() :
		m_Root(NULL)
	{
	}

	// 実行ノードを推論する
	NodeBase *Inference(T *enemy, BehaviorData *data){
		// データをリセットして開始
		data->Init();
		return m_Root->Inference(enemy, data);
	}

	// シーケンスノードから推論開始
	NodeBase *SequenceBack(NodeBase *sequence_node, T *enemy, BehaviorData *data) {
		return sequence_node->Inference(enemy, data);
	}
	
	// ノード追加
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
				printf("ルートは既に登録されています\n");
			}
		}
	};

	// ツリー構造を表示
	void PrintTree()
	{
		if (m_Root != NULL)
		{
			m_Root->PrintName();
		}
	};

	// 実行
	NodeBase *Run(T *enemy, NodeBase *action_node, BehaviorData *data) {
		// ノード実行
		ActionBase::STATE state = action_node->Run(enemy);

		// 正常終了
		if (state == ActionBase::STATE::COMPLETE)
		{
			// シーケンスの途中かを判断
			NodeBase* sequence_node = data->PopSequenceNode();

			// 途中じゃないなら終了
			if (sequence_node == NULL)
			{
				return NULL;
			}
			else {
				// 途中ならそこから始める
				return SequenceBack(sequence_node, enemy, data);
			}
			// 失敗は終了
		}
		else if (state == ActionBase::STATE::FAILED) {
			return NULL;
		}

		// 現状維持
		return action_node;
	}
	;
private:
	// ルートノード
	NodeBase *m_Root;
};

#endif
