cmake_minimum_required(VERSION 3.1)
project(Vici)

#-------------------------------------------------------------------------------------------
# Options
#-------------------------------------------------------------------------------------------
option(VICI_USE_DIRECX "Should DirectX Be used over OpenGL for Windows?" OFF)


# Include project vars
include("ViciBuildSetup.cmake")

#-------------------------------------------------------------------------------------------
# Sub-projects
#-------------------------------------------------------------------------------------------
add_subdirectory(Engine)

if(VICI_EDITOR)
	add_subdirectory(Editor)
endif()

# Build the example / test project
#if(VICI_BUILD_EXAMPLE_PROJECT)
	#add_subdirectory(ExampleProject)
#endif()

#-------------------------------------------------------------------------------------------
# Installation
#-------------------------------------------------------------------------------------------

