cmake_minimum_required(VERSION 3.1)

#-------------------------------------------------------------------------------------------
# Check and Set VICI_HOME
#-------------------------------------------------------------------------------------------
if(DEFINED ENV{VICI_HOME})
	message("Vici home directory = $ENV{VICI_HOME}")
	set(VICI_HOME $ENV{VICI_HOME})
	string(REPLACE "\\" "/" VICI_HOME "${VICI_HOME}")
else()
	message("ERROR! No VICI_HOME Environment variable set, have you run the setup.bat/sh script?")
	return()
endif()

#-------------------------------------------------------------------------------------------
# Ensure Package Manager is configured and Ready
#-------------------------------------------------------------------------------------------
include ("${VICI_HOME}BuildScripts/IncludePackageManager.cmake")

#-------------------------------------------------------------------------------------------
# Start of Project.
#-------------------------------------------------------------------------------------------
project(Vici)

#-------------------------------------------------------------------------------------------
# Build Vars / Functions / Macros helper. (Will declare all Engine modules internally)
#-------------------------------------------------------------------------------------------
include("BuildScripts/ViciBuildHelper.cmake")


#-------------------------------------------------------------------------------------------
# Sub-projects
#-------------------------------------------------------------------------------------------
add_subdirectory(Engine)

if(VICI_EDITOR)
#	add_subdirectory(ViciEditor)

	add_subdirectory(CLI)
	
	if(VICI_WITH_TESTS)
		set (TEST_MODULES Core Engine Platform)
		add_subdirectory(RunTests)
	endif()
endif()

# Build the example / test project
#if(VICI_BUILD_EXAMPLE_PROJECT)
	#add_subdirectory(ExampleProject)
#endif()

#-------------------------------------------------------------------------------------------
# Installation
#-------------------------------------------------------------------------------------------

