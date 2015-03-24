#include "Thread.h"
#include "Vici.h"

VThread::VThread()
{
	//_mutex = PTHREAD_MUTEX_INITIALIZER;
}


VThread::~VThread()
{
}

void VThread::Start(void * (*start_routine) (void *), void* arg)
{
	_id = pthread_create( &_thread, NULL, start_routine, arg);
}

void VThread::LockMutex()
{
	pthread_mutex_lock(&_mutex);
}

void VThread::UnlockMutex()
{
	pthread_mutex_unlock(&_mutex);
}