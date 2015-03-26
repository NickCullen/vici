#include <stdio.h>
#include "Vici.h"
#include "Platform.h"
#include "Thread.h"
#include "TestProj.h"

int main(int argc, char** argv)
{
	Vici* v = new Vici();
	TestProj* proj = new TestProj();

	//print the path given into the program
	_Platform->LogString("Main arg[0] = %s\n", argv[0]);

	_Platform->SetCwd(argv[0], true);

	v->Init();

	v->Begin();

	_Platform->EnterLoop(v);

	delete(v);


	return 0;
}