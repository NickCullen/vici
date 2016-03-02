#include "Editor.h"


int main(int argc, const char** argv)
{
	VEditor editor;
	
	if (editor.Init(argc, argv))
	{
		return editor.Run();
	}
	else
		return -1;
}