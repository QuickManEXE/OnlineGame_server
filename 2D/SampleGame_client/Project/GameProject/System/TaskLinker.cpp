#include "TaskLinker.h"
#include "TaskManager.h"

TaskLinker::TaskLinker() :
	mp_task(nullptr),
	mp_prev(nullptr),	
	mp_next(nullptr),
	m_priority(0)
{

}

TaskLinker::TaskLinker(int priority, Task *task) :
	m_priority(priority),
	mp_prev(nullptr),
	mp_next(nullptr),
	mp_task(task)
{

}

TaskLinker::~TaskLinker()
{

}