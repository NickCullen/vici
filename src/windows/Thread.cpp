#include "Thread.h"
#include "Vici.h"

VThread::VThread()
{
	//_mutex = PTHREAD_MUTEX_INITIALIZER;
}


VThread::~VThread()
{
}

void VThread::Start(THREAD_RETURN(FUNCTION_CALL*start_routine) (THREAD_ARG), THREAD_ARG arg)
{
	_thread = CreateThread(NULL, NULL, start_routine,arg, NULL,&_id);

}

void VThread::LockMutex()
{
	//pthread_mutex_lock(&_mutex);
}

void VThread::UnlockMutex()
{
	//pthread_mutex_unlock(&_mutex);
}