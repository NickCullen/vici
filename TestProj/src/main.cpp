#include <stdio.h>
#include "Vici.h"
#include "Platform.h"

int main(int argc, char** argv)
{
	Vici* v = new Vici();

	//print the path given into the program
	_Platform->LogString("Main arg[0] = %s\n", argv[0]);

	_Platform->SetCwd(argv[0], true);

	v->Init();

	v->Begin();

	_Platform->EnterLoop(v);

	delete(v);

	return 0;
}