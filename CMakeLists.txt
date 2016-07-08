cmake_minimum_required(VERSION 3.1)
project(Vici)

# Include project vars
include("ViciBuildSetup.cmake")

#-------------------------------------------------------------------------------------------
# Output Directories
#-------------------------------------------------------------------------------------------
if(VICI_EDITOR)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${VICI_HOME}Build/Editor/${VICI_TARGET_SYSTEM}/Bin/${VICI_PLATFORM_TARGET}")
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${VICI_HOME}Build/Editor/${VICI_TARGET_SYSTEM}/Lib/${VICI_PLATFORM_TARGET}")
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${VICI_HOME}Build/Editor/${VICI_TARGET_SYSTEM}/Lib/${VICI_PLATFORM_TARGET}")
else()
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${VICI_HOME}Build/${VICI_TARGET_SYSTEM}/Bin/${VICI_PLATFORM_TARGET}")
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${VICI_HOME}Build/${VICI_TARGET_SYSTEM}/Lib/${VICI_PLATFORM_TARGET}")
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${VICI_HOME}Build/${VICI_TARGET_SYSTEM}/Lib/${VICI_PLATFORM_TARGET}")
endif()

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

