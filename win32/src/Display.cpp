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
	rapidxml::xml_document<char> doc;
	TextFile tf(buff);

	if (tf.IsLoaded())
	{
		doc.parse<0>(tf);
		rapidxml::xml_node<char>* root = doc.first_node();

		//see if we should enter full screen
		rapidxml::xml_node<char>* fullscreen_node = root->first_node("fullscreen");
		bool fullscreen = false;
		if (fullscreen_node != NULL)
		{
			fullscreen = (bool)strcmp("false", fullscreen_node->value());
		}

		//if fullscreen set full screen else read w and h
		if (fullscreen)
		{
			printf("\n*** Fullscreen is not yet supported ***\n");
		}
		else
		{
			//width and height
			sscanf((const char*)root->first_node("width")->value(), "%d", &_w);
			sscanf((const char*)root->first_node("height")->value(), "%d", &_h);

			//title
			sprintf(title, "%s", root->first_node("title")->value());
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