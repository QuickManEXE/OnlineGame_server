#pragma once
#include<memory>


namespace AI
{
    /// <summary>
    /// ゴールの状態
    /// </summary>

    enum Status
    {
        Inactive,
        Active,
        Completed,
        Failed,
    };

    /// <summary>
    /// ゴールインターフェース
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
    /// ゴールの基底クラス
    /// </summary>
    template<typename T>
    class Goal : IGoal
    {
    protected:

        T* _owner;

    public:

        /// <summary>
    /// 非アクティブか
    /// </summary>
        bool IsInactive() { return _status == Status.Inactive; }

        /// <summary>
        /// アクティブか
        /// </summary>
        bool IsActive() { return _status == Status.Active; }

        /// <summary>
        /// 完了済か
        /// </summary>
        bool IsCompleted() { return _status == Status.Completed; }

        /// <summary>
        /// ゴール失敗か
        /// </summary>
        bool HasFailed() { return _status == Status.Failed; }

        /// <summary>
        /// 現在のステータス
        /// </summary>
        Status _status = Status.Inactive;

        public Goal<T>(T* owner)
        {
            _owner = owner;
        }


        /// <summary>
        /// 非アクティブならアクティブ状態に移行する
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
                    /// 失敗している場合はアクティブ化を試みる
                    /// </summary>
        void ReactivateIfFailed()
        {
            if (HasFailed)
            {
                _status = Status.Inactive;
            }
        }

        /// <summary>
        /// アクティベイト処理
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
        /// ゴールの後処理
        /// 成功／失敗に関わらず実行される
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