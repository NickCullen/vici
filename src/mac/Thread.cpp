#include "Thread.h"
#include "Vici.h"

VThread::VThread()
{
	int created = pthread_mutex_init(&_mutex, NULL);
	_Platform->LogString("Created = %d\n", created);
}


VThread::~VThread()
{
	_Platform->LogString("Being deleted\n");
	MarkForDeletion();
}

void VThread::Start(void * (*start_routine) (void *), void* arg)
{
	_id = pthread_create( &_thread, NULL, start_routine, arg);
}

void VThread::WaitToEnd(void** ret)
{
	pthread_join(_thread, ret);
}

void VThread::MarkForDeletion()
{
	pthread_detach(_thread);
}

void VThread::Cancel()
{
	pthread_cancel(_thread);
}

void VThread::LockMutex()
{
	pthread_mutex_lock(&_mutex);
}

void VThread::UnlockMutex()
{
	pthread_mutex_unlock(&_mutex);
}

bool VThread::operator==(const VThread& rhs)
{
	return pthread_equal(_thread, rhs._thread) == 1;
}