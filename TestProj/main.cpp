#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Display.h"
#include "Platform.h"
#include "rapidxml/rapidxml.hpp"
#include "TextFile.h"
#include "GameObject.h"
#include "IComponent.h"
#include "Vici.h"
#include "TList.h"

int main(int argc, char** argv)
{
	TList<GameObject> my_list;
	GameObject* one   = new GameObject();
	GameObject* two   = new GameObject();
	GameObject* three = new GameObject();
	GameObject* four  = new GameObject();

	my_list.Add(one);
	my_list.Add(two);
	my_list.Add(three);
	my_list.Add(four);

	//foreach in c++ :D
	TLIST_foreach(GameObject, go, my_list)
	{
		go->Update();
	}

	Vici* v = new Vici();

	v->Init();

	v->Begin();

	Platform_EnterLoop(v);

	return 0;
}