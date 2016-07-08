cmake_minimum_required(VERSION 3.1)
project(ExampleProject)

# Output for this project will be in its own build directory
if(VICI_EDITOR)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Build/Editor/${VICI_TARGET_SYSTEM}/Bin/${VICI_PLATFORM_TARGET}")
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Build/Editor/${VICI_TARGET_SYSTEM}/Lib/${VICI_PLATFORM_TARGET}")
else()
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Build/${VICI_TARGET_SYSTEM}/Bin/${VICI_PLATFORM_TARGET}")
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Build/${VICI_TARGET_SYSTEM}/Lib/${VICI_PLATFORM_TARGET}")
endif()

# Add its own include include_directories
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Code")

# Add its own link include_directories
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

	# Search patterns
	"*.h"
	"*.cpp"
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