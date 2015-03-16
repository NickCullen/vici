cmake_minimum_required (VERSION 2.6)
project(testing)

# Turn on the ability to create folders to organize projects (.vcproj)
# It creates "CMakePredefinedTargets" folder by default and adds CMake
# defined projects like INSTALL.vcproj and ZERO_CHECK.vcproj
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#add preprocessor definitions
if(WIN32)
 	add_definitions(-DVICI_WINDOWS -DVICI_DESKTOP -DVICI_OPENGL -D_CRT_SECURE_NO_WARNINGS)
elseif(APPLE)
	add_definitions(-DVICI_MAC -DVICI_DESKTOP -DVICI_OPENGL)
endif()

#set ThirdParty include path
set(THIRD_PARTY "${PROJECT_SOURCE_DIR}/ThirdParty")

#add third party includes
include_directories("${THIRD_PARTY}")

#engine includes
set(VICI_INCLUDES "${PROJECT_SOURCE_DIR}")
include_directories("${VICI_INCLUDES}")
include_directories("${VICI_INCLUDES}/core")
include_directories("${VICI_INCLUDES}/rendering")
include_directories("${VICI_INCLUDES}/util")
include_directories("${VICI_INCLUDES}/datastructures")
include_directories("${VICI_INCLUDES}/assets")

#win32 build
if(WIN32)
	#link up win32 lib dir
	link_directories("${THIRD_PARTY}/win32/lib")

	#compile platform library for windows
	add_subdirectory(win32)
elseif(APPLE)
	#include the apple frameworks dir
	include_directories("/System/Library/Frameworks")

	#link up mac lib dir
	link_directories("${THIRD_PARTY}/mac/lib")

	#compile platform library for mac
	add_subdirectory(mac)
endif()

#compile engine sources into vlibrary
add_subdirectory(src)

#if the program should compile into lib 
if(BUILD_LIB)

#or should build as an exec with TestProj and test files
else()

	#compile into a executable with the test project
	add_executable(testing TestProj/main.cpp)

	#link up librares
	target_link_libraries(testing debug vlibrary platformlib ${EXTRA_LIBS} ${EXTRA_LIBS_DEBUG})
	target_link_libraries(testing optimized vlibrary platformlib ${EXTRA_LIBS})

	#post build commands (copy dlls and their equivilant etc.)

	if(WIN32)
		#copy contents of win32 bin folder 
		add_custom_command(TARGET testing POST_BUILD
		    COMMAND ${CMAKE_COMMAND} -E copy_directory
		        "${PROJECT_SOURCE_DIR}/win32/bin"
		        $<TARGET_FILE_DIR:testing>)

	elseif(APPLE)
		#copy contents of mac bin folder 
		add_custom_command(TARGET testing POST_BUILD
		    COMMAND ${CMAKE_COMMAND} -E copy_directory
		        "${PROJECT_SOURCE_DIR}/mac/bin"
		        $<TARGET_FILE_DIR:testing>)

	endif()

	#copy contents of TestProj to output dir 
	add_custom_command(TARGET testing POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/TestProj"
        "${CMAKE_CURRENT_BINARY_DIR}")
endif()



