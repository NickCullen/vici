cmake_minimum_required (VERSION 2.6)
project(WindowsProject)

#set vici home
string(REPLACE "\\" "/" VICI_HOME $ENV{VICI_HOME})

# Turn on the ability to create folders to organize projects (.vcproj)
# It creates "CMakePredefinedTargets" folder by default and adds CMake
# defined projects like INSTALL.vcproj and ZERO_CHECK.vcproj
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#add preprocessor definitions
add_definitions(-DVICI_WINDOWS -DVICI_DESKTOP -DVICI_OPENGL -D_CRT_SECURE_NO_WARNINGS)

#add third party includes
set(THIRD_PARTY "${VICI_HOME}ThirdParty")
include_directories("${THIRD_PARTY}")

#engine includes
set(VICI_INCLUDE "${VICI_HOME}include")
include_directories("${VICI_INCLUDE}")
include_directories("${VICI_INCLUDE}/core")
include_directories("${VICI_INCLUDE}/rendering")
include_directories("${VICI_INCLUDE}/util")
include_directories("${VICI_INCLUDE}/datastructures")
include_directories("${VICI_INCLUDE}/assets")
include_directories("${VICI_INCLUDE}/debugging")

#link up win32 lib dir
if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
	message("BUILDING FOR x64")
	link_directories("${THIRD_PARTY}/lib/win64")
	link_directories("${VICI_HOME}build/win64")
else("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
	message("BUILDING FOR x86")
	link_directories("${THIRD_PARTY}/lib/win32")
	link_directories("${VICI_HOME}build/win32")
endif("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")

#find required libaries
find_package(OpenGL REQUIRED)

#include required libraries headers
include_directories(${OPENGL_INCLUDE_DIRS})

#set the extra libs so that they will be compiled
set(LIBS glfw3 glew32 pthreadVC2 ${OPENGL_LIBRARIES})

#set the extra libs so that they will be compiled
set(LIBS_DEBUG vld)

#platform sources will move to here (when being copied)
FILE(GLOB platform_sources "${VICI_HOME}Templates/Windows/src/*.cpp")

#set and include project sources will be a relative path
include_directories("../../src/")
FILE(GLOB project_sources "../../src/*.cpp")

#compile into a executable
add_executable(WindowsProject ${platform_sources} ${project_sources})

#link up librares
target_link_libraries(WindowsProject debug vici ${LIBS} ${LIBS_DEBUG})
target_link_libraries(WindowsProject optimized vici ${LIBS})


#post build commands (copy dlls and their equivilant etc.)
if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
	#copy contents of win64 bin folder 
	add_custom_command(TARGET WindowsProject POST_BUILD
    	COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${THIRD_PARTY}/bin/win64"
        $<TARGET_FILE_DIR:WindowsProject>)
else("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
	#copy contents of win32 bin folder 
	add_custom_command(TARGET WindowsProject POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${THIRD_PARTY}/bin/win32"
        $<TARGET_FILE_DIR:WindowsProject>)
	
endif()

	
#copy contents of WindowsProject to output dir 
add_custom_command(TARGET WindowsProject POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_directory
    "../../Assets"
    $<TARGET_FILE_DIR:WindowsProject>/Assets)

add_custom_command(TARGET WindowsProject POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_directory
    "../../scenes"
    $<TARGET_FILE_DIR:WindowsProject>/scenes)

add_custom_command(TARGET WindowsProject POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_directory
    "../../settings"
    $<TARGET_FILE_DIR:WindowsProject>/settings)