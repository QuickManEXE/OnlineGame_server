#pragma once
#include"CompositeGoal.h"


namespace AI
{
   
    /// <summary>
    /// �S�[���𓝊����郋�[�g�S�[��
    /// </summary>
    template<typename T>
    class Brain : public CompositeGoal<T>
    {
        // �v�����i�[
    private:
        
        IPlanner _planner;

    // ���ݑI������Ă���v����
    PlanBase _currentPlan;

    // �Z���L�����Ă���I�u�W�F�N�g��ێ�
    std::vector<Memory> _shortMemories = new std::vector<Memory>();

    // �����L�����Ă���I�u�W�F�N�g��ێ�
    std::vector<Memory> _longMemories = new std::vector<Memory>();

    /// <summary>
    /// �L�����Ă��邷�ׂẴI�u�W�F�N�g��Ԃ�
    /// </summary>
    private:
        
        std::vector<Memory> AllMemories()
        {
            List<Memory> allMemories = new List<Memory>();
            allMemories.AddRange(_shortMemories);
            allMemories.AddRange(_longMemories);
            return allMemories;
        }

   

            
    public:
        
        // �R���X�g���N�^
        Brain(T owner) : CompositeGoal(owner)
        {
            // NOTE:
            // ����͊ȒP�̂��߃v�����i�[�𒼐ڐ������Ă��邪�A
            // DI�I�ɐݒ肵���ق����ėp���͍���
            _planner = new CharaPlanner(owner);
        }

            /// <summary>
            /// �v�������L���ɕێ�
            /// </summary>
            /// <param name="planObject"></param>
         void Memorize(PlanObject planObject)
            {
            // �d�����Ă���v�����͒ǉ����Ȃ�
            if (HasMemory(planObject))
            {
                return;
            }

            _shortMemories.Add(MakeMemory(planObject));
        }

        /// <summary>
        /// �������R���g���[��
        /// ���łɒB�������v�����ȂǁA�L����������ׂ��I�u�W�F�N�g�����X�g����폜����
        /// </summary>
        void MemoryControl()
        {
            var targets = from m in _shortMemories
                          where m.Target != null
                          select m;

            var newList = targets.ToList();
            _shortMemories = newList;
        }

            /// <summary>
            /// �v�������X�g����œK�ȃv������]���A�擾����
            /// </summary>
            /// <returns></returns>
            PlanBase EvaluatePlans()
            {
                List<PlanBase> plans = EnumeratePlans();
                return _planner.Evaluate(plans);
            }

        /// <summary>
        /// �Z���E�����L���o���ɕێ����Ă���v������񋓂���
        /// </summary>
        /// <returns></returns>
        std::vector<PlanBase> EnumeratePlans()
        {
            var plans = new List<PlanBase>();
            foreach(var m in AllMemories)
            {
                plans.Add(m.Plan);
            }
            return plans;
        }

        /// <summary>
        /// �v�����ɉ����ăS�[����I������
        /// </summary>
        /// <param name="plan"></param>
        /// <returns></returns>
        IGoal GetGoalByPlan(PlanBase plan)
        {
            switch (plan.GoalType)
            {
                // �������T�����
                case GoalType.Wander:
                {
                    return new GoalWander<T>(_owner);
                }

                // �G�l���M�[�^�p���[�𓾂�
                case GoalType.GetEnergy:
                case GoalType.GetPower:
                {
                    var memory = FindMemory(plan);
                    return new GoalGetItem<T>(_owner, memory.Target);
                }

                // �G���U��
                case GoalType.Attack:
                {
                    var memory = FindMemory(plan);
                    return new GoalAttackTarget<T>(_owner, memory.Target);
                }
            }

            return new Goal<T>(_owner);
        }

        /// <summary>
        /// �I�𒆂̃v��������v������ύX����
        /// </summary>
        /// <param name="newPlan"></param>
        void ChangePlan(PlanBase newPlan)
        {
            Debug.Log("Change plan to " + newPlan);

            _currentPlan = newPlan;
            RemoveAllSubgoals();

            var goal = GetGoalByPlan(newPlan);
            AddSubgoal(goal);
        }

        /// <summary>
        /// �v�����I�u�W�F�N�g���烁�����I�u�W�F�N�g�𐶐�����
        /// </summary>
        Memory MakeMemory(PlanObject planObject)
        {
            var memory = new Memory(planObject);
            return memory;
        }

        /// <summary>
        /// �Ώۃv��������L���I�u�W�F�N�g������
        /// </summary>
        Memory FindMemory(PlanBase plan)
        {
            return AllMemories.Find(m = > m.Plan == plan);
        }

        /// <summary>
        /// �L���ɂ���v������
        /// </summary>
        bool HasMemory(PlanObject planObject)
        {
            var memory = AllMemories.Find(m = > m.Plan == planObject.Plan);
            return memory != null;
        }

        /// <summary>
        /// �L���ɂ��郁������
        /// </summary>
        bool HasMemory(Memory memory)
        {
            var storeMem = AllMemories.Find(m = > m == memory);
            return storeMem != null;
        }

        public override void Activate()
        {
            base.Activate();

            RemoveAllSubgoals();

            // �Ȃɂ��Ȃ��Ƃ��ɂ������������v������ݒ肵�Ă���
            var memory = new Memory();
            memory.Plan = new PlanWander();

            _longMemories.Add(memory);
        }

        public override Status Process()
        {
            ActivateIfInactive();

            PlanBase selectedPlan = EvaluatePlans();
            bool needsChangePlan = (selectedPlan != null) && (_currentPlan != selectedPlan);
            if (needsChangePlan)
            {
                ChangePlan(selectedPlan);
            }

            return ProcessSubgoals();
        }

        public override void Terminate()
        {
            base.Terminate();
        }

      
    };
}