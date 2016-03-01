#include "Editor.h"


int main(int argc, int argv)
{
	VEditor editor;

	if (editor.Init(argc, argv))
	{
		return editor.Run();
	}
	else
		return -1;
}