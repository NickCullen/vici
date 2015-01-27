#include <stdio.h>
#include "Vici.h"
#include "Platform.h"

int main(int argc, char** argv)
{
	Vici* v = new Vici();

	v->Init();

	v->Begin();

	Platform_EnterLoop(v);

	return 0;
}