#include <stdio.h>
#include "Display.h"
#include "Platform.h"
#include "rapidxml/rapidxml.hpp"
#include "TextFile.h"
#include "GameObject.h"
#include "IComponent.h"
#include "Vici.h"

int main(int argc, char** argv)
{
	Vici* v = new Vici();

	v->Init();

	v->Begin();

	Platform_EnterLoop(v);

	return 0;
}