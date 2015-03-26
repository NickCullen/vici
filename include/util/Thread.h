#ifndef V_THREAD
#define V_THREAD

#include "PlatformDefinitions.h"

/**
* Class responsible for creating, running and stopping threads
* acts as a wrapper around the actual underlying OS threading
* system
*/

class VThread
{
private:
	PlatformThreadType _thread;	/**< The operating system specific thread (see PlatformDefinitions.h) */

	PlatformMutexType _mutex;	/**> Mutex associated with this thread */

	ThreadID _id;	/**< Thread id - set when thread is created */
public:

	/**
	* Default Constructor
	*/
	VThread();

	/**
	* Default destructor
	*/
	~VThread();

	/**
	* Starts executing the thread - 
	* @param start_routine The function that will be executed on a new thread
	* @param arg void* arguments to the thread
	* @return Integer representing the return value of the thread
	*/
	void Start(void*(*start_routine) (void*), void* arg);

	/**
	* Waits for the thread to stop executing
	* either by exitting or being cancelled
	* @param ret pointer to the Return value of thread
	*/
	void WaitToEnd(void** ret);

	/**
	* Cancels the thread
	*/
	void Cancel();

	/**
	* Marks the thread for deletion
	*/
	void MarkForDeletion();
	
	/**
	* Lock the mutex
	*/
	void LockMutex();

	/**
	* Unlock the mutex
	*/
	void UnlockMutex();

	/**
	* Overrides the == operator to check if threads are the same
	* @param rhs The right hand side parameter of ==
	* @return bool True if equal
	*/
	bool operator==(const VThread& rhs);
};



#endif