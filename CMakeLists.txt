cmake_minimum_required(VERSION 3.1)
project(Vici)

#-------------------------------------------------------------------------------------------
# First checks
#-------------------------------------------------------------------------------------------
if(DEFINED ENV{VICI_HOME})
	message("Vici home directory = $ENV{VICI_HOME}")
	set(VICI_HOME $ENV{VICI_HOME})
	set(VICI_THIRD_PARTY_DIR "$ENV{VICI_HOME}ThirdParty/")
else()
	message("ERROR! No VICI_HOME Environment variable set, have you run the setup.bat/sh script?")
	return()
endif()

#-------------------------------------------------------------------------------------------
# Options
#-------------------------------------------------------------------------------------------
option(VICI_USE_DIRECTX "Use DirectX on Windows builds" OFF)
option(VICI_EDITOR_BUILD "Use to build editor methods and functionality into the engine" ON)

#-------------------------------------------------------------------------------------------
# Defines
#-------------------------------------------------------------------------------------------
add_definitions(-D_CRT_SECURE_NO_WARNINGS)

# Common Defines
if(${CMAKE_SIZEOF_VOID_P} EQUAL 8)
	message("64 Bit build")
	add_definitions(-DVICI_64BIT)
	set(VICI_64BIT 1)
else()
	message("32 bit build")
	add_definitions(-DVICI_32BIT)
	set(VICI_32BIT 1)
endif()

# Editor build or not?
if(VICI_EDITOR_BUILD)
	add_definitions(-DVICI_EDITOR)
	set(VICI_EDITOR 1)
endif()

# Windows Defines
if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	message("Windows Build")

	add_definitions(-DVICI_WINDOWS)
	add_definitions(-DVICI_WIN32)
	add_definitions(-DVICI_PC)
	set(VICI_WINDOWS 1)
	set(VICI_WIN32 1)
	set(VICI_PC 1)

	# Use vici use Direct X? 
	if(VICI_USE_DIRECX)
		add_definitions(-DVICI_DIRECTX)
		set(VICI_DIRECTX 1)
	else()
		add_definitions(-DVICI_OPENGL)
		set(VICI_OPENGL 1)
	endif()

	# Set these so we can traverse the correct folders easily
	set(VICI_TARGET_SYSTEM "Win32")
	if(VICI_32BIT)
		set(VICI_PLATFORM_TARGET "x86")
	else()
		set(VICI_PLATFORM_TARGET "x64")
	endif()

# Mac Defines
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
	message("Mac Build")

	add_definitions(-DVICI_MAC)
	add_definitions(-DVICI_PC)
	set(VICI_MAC 1)
	set(VICI_PC 1)

	# Graphics 
	add_definitions(-DVICI_OPENGL)
	set(VICI_OPENGL 1)

	# Set these so we can traverse the correct folders easily
	set(VICI_TARGET_SYSTEM "Mac")
	if(VICI_32BIT)
		set(VICI_PLATFORM_TARGET "x86")
	else()
		set(VICI_PLATFORM_TARGET "x64")
	endif()

# Linux Defines
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
	message("Linux Build")

	add_definitions(-DVICI_LINUX)
	add_definitions(-DVICI_PC)
	set(VICI_LINUX 1)
	set(VICI_PC 1)

	# Graphics
	add_definitions(-DVICI_OPENGL)
	set(VICI_OPENGL 1)

	# Set these so we can traverse the correct folders easily
	set(VICI_TARGET_SYSTEM "Linux")
	if(VICI_32BIT)
		set(VICI_PLATFORM_TARGET "x86")
	else()
		set(VICI_PLATFORM_TARGET "x64")
	endif()
endif()


#-------------------------------------------------------------------------------------------
# Compiler Flags
#-------------------------------------------------------------------------------------------
set (CMAKE_CXX_STANDARD 11)


#-------------------------------------------------------------------------------------------
# Output Directories
#-------------------------------------------------------------------------------------------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${VICI_HOME}Build/${VICI_TARGET_SYSTEM}/Bin/${VICI_PLATFORM_TARGET}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${VICI_HOME}Build/${VICI_TARGET_SYSTEM}/Lib/${VICI_PLATFORM_TARGET}")

#-------------------------------------------------------------------------------------------
# Include dirs
#-------------------------------------------------------------------------------------------
include_directories(Engine)

#-------------------------------------------------------------------------------------------
# Libraries		- Make sure all modules can find each other
#-------------------------------------------------------------------------------------------
link_directories("${VICI_HOME}Build/${VICI_TARGET_SYSTEM}/Lib/${VICI_PLATFORM_TARGET}")

#-------------------------------------------------------------------------------------------
# Sub-projects
#-------------------------------------------------------------------------------------------
add_subdirectory(Engine)

#-------------------------------------------------------------------------------------------
# Installation
#-------------------------------------------------------------------------------------------

