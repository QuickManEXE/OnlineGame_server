#pragma once
#include<memory>


namespace AI
{
    /// <summary>
    /// �S�[���̏��
    /// </summary>

    enum Status
    {
        Inactive,
        Active,
        Completed,
        Failed,
    };

    /// <summary>
    /// �S�[���C���^�[�t�F�[�X
    /// </summary>
    class IGoal
    {
        bool IsInactive;
        bool IsActive;
        bool IsCompleted;
        bool HasFailed;

        virtual void Activate()=0;
        virtual Status Process()=0;
        virtual void Terminate()=0;
        virtual void AddSubgoal(IGoal subgoal)=0;
        virtual ~IGoal() = 0;
    };

    /// <summary>
    /// �S�[���̊��N���X
    /// </summary>
    template<typename T>
    class Goal : IGoal
    {
    protected:

        T* _owner;

    public:

        /// <summary>
    /// ��A�N�e�B�u��
    /// </summary>
        bool IsInactive() { return _status == Status.Inactive; }

        /// <summary>
        /// �A�N�e�B�u��
        /// </summary>
        bool IsActive() { return _status == Status.Active; }

        /// <summary>
        /// �����ς�
        /// </summary>
        bool IsCompleted() { return _status == Status.Completed; }

        /// <summary>
        /// �S�[�����s��
        /// </summary>
        bool HasFailed() { return _status == Status.Failed; }

        /// <summary>
        /// ���݂̃X�e�[�^�X
        /// </summary>
        Status _status = Status.Inactive;

        public Goal<T>(T* owner)
        {
            _owner = owner;
        }


        /// <summary>
        /// ��A�N�e�B�u�Ȃ�A�N�e�B�u��ԂɈڍs����
        /// </summary>
        void ActivateIfInactive()
        {
            if (IsInactive)
            {
                Activate();
            }
        }


    protected:

        /// <summary>
                    /// ���s���Ă���ꍇ�̓A�N�e�B�u�������݂�
                    /// </summary>
        void ReactivateIfFailed()
        {
            if (HasFailed)
            {
                _status = Status.Inactive;
            }
        }

        /// <summary>
        /// �A�N�e�B�x�C�g����
        /// </summary>
        virtual void Activate()
        {
            Debug.Log("Start " + this);

            _status = Status.Active;
        }

        virtual Status Process()
        {
            ActivateIfInactive();
            return _status;
        }

        /// <summary>
        /// �S�[���̌㏈��
        /// �����^���s�Ɋւ�炸���s�����
        /// </summary>
        virtual void Terminate()
        {
            // do nothing.
        }

        virtual void AddSubgoal(IGoal subgoal)
        {
            // do nothing.
        }
    };
}