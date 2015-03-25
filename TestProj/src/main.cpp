#include <stdio.h>
#include "Vici.h"
#include "Platform.h"
#include "Thread.h"


void* MyThreadFunc(void* args)
{
	_Platform->LogString("In MyThreadFunc\n");

	return NULL;
}

void Tests()
{
	VThread thread;

	thread.Start(&MyThreadFunc, NULL);

}


int main(int argc, char** argv)
{
	Vici* v = new Vici();

	//execute tests
	Tests();

	//print the path given into the program
	_Platform->LogString("Main arg[0] = %s\n", argv[0]);

	_Platform->SetCwd(argv[0], true);

	v->Init();

	v->Begin();

	_Platform->EnterLoop(v);

	delete(v);


	return 0;
}