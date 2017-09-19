#include "Window.h"
#include <stdio.h>

int main(int argc, char** argv)
{
	Core::VString str1 = "Hello";
	Core::VString str2 = ", World";

	Core::VString str3 = str1 + str2 + "!";


	uint32 loc = str3.FirstIndexOf("Wo");
	if (loc != Core::VString::INVALID_POS)
	{
		printf("FOUND\n!");
	}

	loc = str3.LastIndexOf(str2 + "!");
	if (loc != Core::VString::INVALID_POS)
	{
		printf("FOUND LAST OF\n!");
	}

	Core::VString SubStr = str3.GetSubstr(str3.GetLength()-1, 3);

	Platform::VWindow w;

	w.Open(10, 100, 100, 200);
	
	while(w.IsOpen())
	{
		w.PollEvents();
	}

	return 0;
}



