cmake_minimum_required (VERSION 2.6)
project(testing)

# Turn on the ability to create folders to organize projects (.vcproj)
# It creates "CMakePredefinedTargets" folder by default and adds CMake
# defined projects like INSTALL.vcproj and ZERO_CHECK.vcproj
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#add preprocessor definitions
if(WIN32)
	set(VICI_WINDOWS 1)
 	add_definitions(-DVICI_WINDOWS -DVICI_DESKTOP -DVICI_OPENGL -D_CRT_SECURE_NO_WARNINGS)
elseif(APPLE)
	set(VICI_MAC 1)
	add_definitions(-DVICI_MAC -DVICI_DESKTOP -DVICI_OPENGL)
endif()

#set ThirdParty include path
set(THIRD_PARTY "${PROJECT_SOURCE_DIR}/ThirdParty")

#add third party includes
include_directories("${THIRD_PARTY}")

#engine includes
set(VICI_INCLUDES "${PROJECT_SOURCE_DIR}/include")
include_directories("${VICI_INCLUDES}")
include_directories("${VICI_INCLUDES}/core")
include_directories("${VICI_INCLUDES}/rendering")
include_directories("${VICI_INCLUDES}/util")
include_directories("${VICI_INCLUDES}/datastructures")
include_directories("${VICI_INCLUDES}/assets")
include_directories("${VICI_INCLUDES}/debugging")

#win32 build
if(${VICI_WINDOWS})
	message("WINDOWS BUILD")

	#link up win32 lib dir
if(${VICI_TARGET_32})
	message("BUILDING FOR x86")
	link_directories("${THIRD_PARTY}/lib/win32")
else(${VICI_TARGET_64})
	message("BUILDING FOR x64")
	link_directories("${THIRD_PARTY}/lib/win64")
endif()

elseif(${VICI_MAC})
	message("MAC BUILD")
	#include the apple frameworks dir
	include_directories("/System/Library/Frameworks")

	#link up mac lib dir
	link_directories("${THIRD_PARTY}/lib/mac")
endif()

#compile engine sources into vlibrary
add_subdirectory(src)

#if the program should compile into lib 
if(BUILD_LIB)

#or should build as an exec with TestProj and test files
else()

	#compile into a executable with the test project
	add_executable(testing TestProj/src/main.cpp)

	#link up librares
	target_link_libraries(testing debug vlibrary ${EXTRA_LIBS} ${EXTRA_LIBS_DEBUG})
	target_link_libraries(testing optimized vlibrary ${EXTRA_LIBS})

	#post build commands (copy dlls and their equivilant etc.)

	if(WIN32)

		if(${VICI_TARGET_32})
			#copy contents of win32 bin folder 
		add_custom_command(TARGET testing POST_BUILD
		    COMMAND ${CMAKE_COMMAND} -E copy_directory
		        "${THIRD_PARTY}/bin/win32"
		        $<TARGET_FILE_DIR:testing>)
		else(${VICI_TARGET_64})
			#copy contents of win64 bin folder 
		add_custom_command(TARGET testing POST_BUILD
		    COMMAND ${CMAKE_COMMAND} -E copy_directory
		        "${THIRD_PARTY}/bin/win64"
		        $<TARGET_FILE_DIR:testing>)
		endif()

		

	elseif(APPLE)
		#copy contents of mac bin folder 
		add_custom_command(TARGET testing POST_BUILD
		    COMMAND ${CMAKE_COMMAND} -E copy_directory
		        "${THIRD_PARTY}/bin/mac"
		        $<TARGET_FILE_DIR:testing>)

	endif()

	#copy contents of TestProj to output dir 
	add_custom_command(TARGET testing POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/TestProj"
        $<TARGET_FILE_DIR:testing>)
endif()



