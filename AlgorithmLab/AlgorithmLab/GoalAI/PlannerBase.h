#pragma once



namespace AI
{
    /// <summary>
    /// プランナーインターフェース
    /// </summary>
    class IPlanner
    {
        virtual float EvaluatePlan(PlanBase plan)=0;
        virtual PlanBase Evaluate(List<PlanBase> plans)=0;
    }

    /// <summary>
    /// プランナーのベースクラス
    ///
    /// プランリストから適切なプランを選択する
    /// </summary>
    class PlannerBase : IPlanner: AIBase
    {
        protected T _owner;


            // コンストラクタ
            public PlannerBase(T owner)
            {
                _owner = owner;
            }

            


                /// <summary>
                /// プランリストを評価して、報酬見込みが一番高いものを返す
                /// </summary>
                /// <param name="plans">評価対象のプランリスト</param>
                /// <returns>選択されたプラン</returns>
                public virtual PlanBase Evaluate(List<PlanBase> plans)
                {
                    float maxValue = 0f;
                    PlanBase selectedPlan = null;
                    foreach(var plan in plans)
                    {
                        float value = EvaluatePlan(plan);
                        if (maxValue <= value)
                        {
                            maxValue = value;
                            selectedPlan = plan;
                        }
                    }

                    return selectedPlan;
                }

            /// <summary>
            /// プランを評価する
            /// </summary>
            /// <param name="plan">評価対象のプラン</param>
            /// <returns>オーナーの現在の状態を加味したプランに応じた報酬見込み値</returns>
            public virtual float EvaluatePlan(PlanBase plan)
            {
                return 0f;
            }
    }
}