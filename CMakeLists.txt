cmake_minimum_required(VERSION 3.1)
project(Vici)

#-------------------------------------------------------------------------------------------
# Build Vars / Functions / Macros helper. (Will declare all Engine modules internally)
#-------------------------------------------------------------------------------------------
include("CMake/ViciBuildHelper.cmake")


#-------------------------------------------------------------------------------------------
# Sub-projects
#-------------------------------------------------------------------------------------------
add_subdirectory(Engine)

#if(VICI_EDITOR)
#	add_subdirectory(ViciEditor)
#endif()

# Build the example / test project
#if(VICI_BUILD_EXAMPLE_PROJECT)
	#add_subdirectory(ExampleProject)
#endif()

#-------------------------------------------------------------------------------------------
# Installation
#-------------------------------------------------------------------------------------------

