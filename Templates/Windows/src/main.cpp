#include <stdio.h>
#include "Vici.h"
#include "Platform.h"
#include "Thread.h"
#include "ViciProject.h"

int main(int argc, char** argv)
{
	Vici* v = new Vici();
	ViciProject* proj = new ViciProject();

	//print the path given into the program
	_Platform->LogString("Main arg[0] = %s\n", argv[0]);

	_Platform->SetCwd(argv[0], true);

	v->Init();

	v->Begin();

	_Platform->EnterLoop(v);

	delete(v);
	delete(proj);

	return 0;
}

