cmake_minimum_required(VERSION 3.1)
project(ExampleProject)

#-------------------------------------------------------------------------------------------
# Common project vars amoungst Vici projects
#-------------------------------------------------------------------------------------------
include("$ENV{VICI_HOME}ViciBuildSetup.cmake")

#-------------------------------------------------------------------------------------------
# Include Directories
#-------------------------------------------------------------------------------------------
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Code")

#-------------------------------------------------------------------------------------------
# Link Directories
#-------------------------------------------------------------------------------------------
if(VICI_EDITOR)
	link_directories("${CMAKE_CURRENT_SOURCE_DIR}/Build/Editor/${VICI_TARGET_SYSTEM}/Lib/${VICI_PLATFORM_TARGET}")
else()
	link_directories("${CMAKE_CURRENT_SOURCE_DIR}/Build/${VICI_TARGET_SYSTEM}/Lib/${VICI_PLATFORM_TARGET}")
endif()

#-------------------------------------------------------------------------------------------
# Source Files
#-------------------------------------------------------------------------------------------
file(GLOB_RECURSE PROJECT_SOURCES 
	LIST_DIRECTORIES false
	RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"

	# Code
	"Code/*.h"
	"Code/*.cpp"

	# Intermediate asset files
	"Assets/*.xml"
	"Settings/*.xml"
)


#-------------------------------------------------------------------------------------------
# Build to shared library
#-------------------------------------------------------------------------------------------
add_library(ExampleProjectLib SHARED 
	${PROJECT_SOURCES}	
)

#-------------------------------------------------------------------------------------------
# Modules this library depends upon
#-------------------------------------------------------------------------------------------
target_link_libraries(ExampleProjectLib PRIVATE PIL Core)
if(VICI_EDITOR)
	target_link_libraries(ExampleProjectLib PRIVATE ViciEditor)
endif()


#-------------------------------------------------------------------------------------------
# Executable Sources
#-------------------------------------------------------------------------------------------
if(VICI_PC)
	file(GLOB EXECUTABLE_SOURCES 
		"${VICI_HOME}/Platforms/Standalone/Code/*.cpp"
	)
endif()

#-------------------------------------------------------------------------------------------
# Build Executable (if needed)
#-------------------------------------------------------------------------------------------
if(VICI_PC)
	add_executable(ExampleProject ${EXECUTABLE_SOURCES})
	target_link_libraries(ExampleProject PRIVATE ExampleProjectLib PIL Core)
endif()


# Filter sources for cleaner project structure
FILTER_SOURCES("${PROJECT_SOURCES}")

# Copy vici runtimes
COPY_VICI_RUNTIMES(ExampleProjectLib)
