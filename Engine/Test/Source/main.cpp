#include "gtest/gtest.h"
#include "Window.h"
#include "VString.h"
int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();

	Platform::VWindow win;

	win.Open(20, 20, 500, 500);

	while (win.IsOpen())
	{
		win.PollEvents();
	}

	return 0;
}



