#pragma once
#include"GoalAI.h"
#include<vector>

namespace AI
{
    /// <summary>
    /// �T�u�S�[�������S�[��
    /// </summary>
    template<typename T>
    class CompositeGoal : Goal<T>
    {
        /// <summary>
        /// �T�u�S�[���̃��X�g
        /// </summary>
    protected:

        std::vector<IGoal> _subgoals = new std::vector<IGoal>();


    public:
        // �R���X�g���N�^
        CompositeGoal(T owner) : base(owner) { }


        Status Process()override
        {
            ActivateIfInactive();
            return ProcessSubgoals();
        }


    public:

        /// <summary>
    /// �T�u�S�[����ǉ�
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
        /// ���ׂẴT�u�S�[�����I�������A�N���A����
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
        /// �T�u�S�[����]������
        /// </summary>
        /// <returns></returns>

    public:

        virtual Status ProcessSubgoals()
        {
            // �T�u�S�[�����X�g�̒��Ŋ��� or ���s�̃S�[�������ׂďI�������A���X�g����폜����
            while (_subgoals.Count > 0 &&
                (_subgoals[0].IsCompleted || _subgoals[0].HasFailed))
            {
                _subgoals[0].Terminate();
                _subgoals.RemoveAt(0);
            }

            // �T�u�S�[�����Ȃ��Ȃ����犮���B
            if (_subgoals.Count == 0)
            {
                _status = Status.Completed;
                return _status;
            }

            auto firstGoal = _subgoals[0];

            // �c���Ă���T�u�S�[���̍őO�̃S�[����]������
            auto subgoalStatus = firstGoal.Process();

            // �őO�̃S�[�����������Ă��āA���܂��T�u�S�[�����c���Ă���ꍇ�͏������p������
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