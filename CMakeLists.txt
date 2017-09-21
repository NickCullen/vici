cmake_minimum_required(VERSION 3.1)

# No real nice way to do this for external projects...
if(DEFINED ENV{VICI_HOME})
	message("Vici home directory = $ENV{VICI_HOME}")
	set(TEMP_VICI_HOME $ENV{VICI_HOME})
	string(REPLACE "\\" "/" TEMP_VICI_HOME "${TEMP_VICI_HOME}")
	set(VICI_THIRD_PARTY_DIR "$ENV{TEMP_VICI_HOME}ThirdParty/")

	include("${TEMP_VICI_HOME}CMake/IncludePackageManager.cmake")
else()
	message("ERROR! No VICI_HOME Environment variable set, have you run the setup.bat/sh script?")
	return()
endif()

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

