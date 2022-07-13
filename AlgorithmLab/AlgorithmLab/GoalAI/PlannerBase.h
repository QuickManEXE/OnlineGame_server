#pragma once



namespace AI
{
    /// <summary>
    /// �v�����i�[�C���^�[�t�F�[�X
    /// </summary>
    class IPlanner
    {
        virtual float EvaluatePlan(PlanBase plan)=0;
        virtual PlanBase Evaluate(List<PlanBase> plans)=0;
    }

    /// <summary>
    /// �v�����i�[�̃x�[�X�N���X
    ///
    /// �v�������X�g����K�؂ȃv������I������
    /// </summary>
    class PlannerBase : IPlanner: AIBase
    {
        protected T _owner;


            // �R���X�g���N�^
            public PlannerBase(T owner)
            {
                _owner = owner;
            }

            


                /// <summary>
                /// �v�������X�g��]�����āA��V�����݂���ԍ������̂�Ԃ�
                /// </summary>
                /// <param name="plans">�]���Ώۂ̃v�������X�g</param>
                /// <returns>�I�����ꂽ�v����</returns>
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
            /// �v������]������
            /// </summary>
            /// <param name="plan">�]���Ώۂ̃v����</param>
            /// <returns>�I�[�i�[�̌��݂̏�Ԃ����������v�����ɉ�������V�����ݒl</returns>
            public virtual float EvaluatePlan(PlanBase plan)
            {
                return 0f;
            }
    }
}