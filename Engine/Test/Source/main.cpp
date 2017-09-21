#include "gtest/gtest.h"
#include "Window.h"

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);

	int ret =  RUN_ALL_TESTS();

	Platform::VWindow win;

	win.Open(30, 30, 600, 600);

	while(win.IsOpen())
	{
		win.PollEvents();
	}

	return ret;
}



