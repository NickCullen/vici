cmake_minimum_required (VERSION 2.6)
project(testing)

# Turn on the ability to create folders to organize projects (.vcproj)
# It creates "CMakePredefinedTargets" folder by default and adds CMake
# defined projects like INSTALL.vcproj and ZERO_CHECK.vcproj
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#engine includes
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/src/core")
include_directories("${PROJECT_SOURCE_DIR}/src/rendering")
include_directories("${PROJECT_SOURCE_DIR}/src/util")
include_directories("${PROJECT_SOURCE_DIR}/src/datastructures")

#compile engine sources into vlibrary
add_subdirectory(src)

#win32 build
if(WIN32)
	# Set compiler flags and options. 
	# Here it is setting the Visual Studio warning level to 4
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")

	#link up win32 lib dir
	link_directories("${PROJECT_SOURCE_DIR}/win32/lib")

	#add windows sub dir
	add_subdirectory(win32)
elseif(APPLE)
	include_directories("/System/Library/Frameworks")

	# Set compiler flags and options. 
	# Here it is setting the Visual Studio warning level to 4
	#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")

	#link up win32 lib dir
	link_directories("${PROJECT_SOURCE_DIR}/mac/lib")

	#add windows sub dir
	add_subdirectory(mac)
endif()

#compile
add_executable(testing TestProj/main.cpp)

message("Included libraries = ${EXTRA_LIBS}")

#link up librares
target_link_libraries(testing vlibrary platformlib ${EXTRA_LIBS})

#post build commands (copy dlls and their equivilant etc.)

if(WIN32)
#copy contents of win32 bin folder 
add_custom_command(TARGET testing POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/win32/bin"
        $<TARGET_FILE_DIR:testing>)
endif()

#copy contents of TestProj to output dir 
add_custom_command(TARGET testing POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/TestProj"
        "${CMAKE_CURRENT_BINARY_DIR}")