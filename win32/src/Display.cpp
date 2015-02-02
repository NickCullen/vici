#include "Display.h"
#include "core.h"
#include <string>

int Display::_w = 0;
int Display::_h = 0;
VWindow* Display::_window = NULL;

Display::Display()
{

}
Display::~Display()
{

}

void Display::Init(char* cwd)
{
	char title[256];
	char buff[758];

	//set the file path
	strcpy(buff, cwd);
	strcat(buff, "\\settings\\display.xml");

	//instantiate doc and load file
	XmlDocument doc;

	if (doc.Load(buff))
	{
		XmlNode root = doc.Root();

		//see if we should enter full screen
		XmlNode fullscreen_node = root.GetChild("fullscreen");
		bool fullscreen = false;
		if (!fullscreen_node.IsNull())
		{
			fullscreen = fullscreen_node.ValueBool();
		}

		//if fullscreen set full screen else read w and h
		if (fullscreen)
		{
			printf("\n*** Fullscreen is not yet supported ***\n");
		}
		else
		{
			//width and height
			_w = root.GetInt("width");
			_h = root.GetInt("height");

			//title
			strcpy(title, root.GetString("title"));
		}

		//open the window
		_window = Platform_OpenWindow(_w, _h, title);
	}
	else
	{
		printf("Could not find display settings xml file!\n");
	}
}

void Display::SetSize(int w, int h, bool force_window_resize)
{
	_w = w;
	_h = h;

	if (force_window_resize)
	{
#ifdef VICI_WINDOWS
		glfwSetWindowSize(_window, _w, _h);
#endif
#ifdef VICI_MAC
		glfwSetWindowSize(_window, _w, _h);
#endif
	}
}

void Display::OnResize(VWindow* win, int w, int h)
{
	_w = w;
	_h = h;
}