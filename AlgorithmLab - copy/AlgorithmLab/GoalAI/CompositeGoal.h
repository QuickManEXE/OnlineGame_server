#pragma once
#include"GoalAI.h"
#include<vector>

namespace AI
{
    /// <summary>
    /// サブゴールを持つゴール
    /// </summary>
    template<typename T>
    class CompositeGoal : Goal<T>
    {
        /// <summary>
        /// サブゴールのリスト
        /// </summary>
    protected:

        std::vector<IGoal> _subgoals = new std::vector<IGoal>();


    public:
        // コンストラクタ
        CompositeGoal(T owner) : base(owner) { }


        Status Process()override
        {
            ActivateIfInactive();
            return ProcessSubgoals();
        }


    public:

        /// <summary>
    /// サブゴールを追加
    /// </summary>
    /// <param name="subgoal"></param>
        void AddSubgoal(IGoal subgoal)override
        {
            if (_subgoals.Contains(subgoal))
            {
                return;
            }

            _subgoals.push_back(subgoal);
        }


        /// <summary>
        /// すべてのサブゴールを終了させ、クリアする
        /// </summary>
    protected:

        void RemoveAllSubgoals()
        {
            foreach(var goal in _subgoals)
            {
                goal.Terminate();
            }

            _subgoals.Clear();
        }

        /// <summary>
        /// サブゴールを評価する
        /// </summary>
        /// <returns></returns>

    public:

        virtual Status ProcessSubgoals()
        {
            // サブゴールリストの中で完了 or 失敗のゴールをすべて終了させ、リストから削除する
            while (_subgoals.Count > 0 &&
                (_subgoals[0].IsCompleted || _subgoals[0].HasFailed))
            {
                _subgoals[0].Terminate();
                _subgoals.RemoveAt(0);
            }

            // サブゴールがなくなったら完了。
            if (_subgoals.Count == 0)
            {
                _status = Status.Completed;
                return _status;
            }

            auto firstGoal = _subgoals[0];

            // 残っているサブゴールの最前のゴールを評価する
            auto subgoalStatus = firstGoal.Process();

            // 最前のゴールが完了していて、かつまだサブゴールが残っている場合は処理を継続する
            if ((subgoalStatus == Status.Completed) &&
                _subgoals.Count > 1)
            {
                _status = Status.Active;
                return _status;
            }

            return _status;
        }
    };
}