#include "Window.h"
#include "gtest/gtest.h"

using namespace Platform;

TEST(VWindow, DefaultConstructor) {
    VWindow win;

    EXPECT_FALSE(win.IsOpen());
}