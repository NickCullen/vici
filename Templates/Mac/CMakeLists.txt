cmake_minimum_required (VERSION 2.6)
project(MacProject)

#set vici home
string(REPLACE "\\" "/" VICI_HOME $ENV{VICI_HOME})

# Turn on the ability to create folders to organize projects (.vcproj)
# It creates "CMakePredefinedTargets" folder by default and adds CMake
# defined projects like INSTALL.vcproj and ZERO_CHECK.vcproj
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#add preprocessor definitions
add_definitions(-DVICI_MAC -DVICI_DESKTOP -DVICI_OPENGL)

#add third party includes
set(THIRD_PARTY "${VICI_HOME}/ThirdParty")
include_directories("${THIRD_PARTY}")
include_directories("${THIRD_PARTY}/squirrel")

#engine includes
set(VICI_INCLUDE "${VICI_HOME}/include")
include_directories("${VICI_INCLUDE}")
include_directories("${VICI_INCLUDE}/core")
include_directories("${VICI_INCLUDE}/rendering")
include_directories("${VICI_INCLUDE}/util")
include_directories("${VICI_INCLUDE}/datastructures")
include_directories("${VICI_INCLUDE}/assets")
include_directories("${VICI_INCLUDE}/debugging")

#link up mac lib dir
link_directories("${THIRD_PARTY}/lib/mac")
link_directories("${VICI_HOME}/build/mac")
#include the apple frameworks dir
include_directories("/System/Library/Frameworks")

#find required libaries
find_package(OpenGL REQUIRED)
find_library(COCOA_LIB cocoa)
find_library(IOKIT_LIB IOKit)
find_library(COREVIDEO_LIB CoreVideo)

MARK_AS_ADVANCED (COCOA_LIB
                 IOKIT_LIB
                 COREVIDEO_LIB)

#include required libraries headers
include_directories(${OPENGL_INCLUDE_DIRS})

#set the extra libs so that they will be compiled
#set the extra libs so that they will be compiled
set(LIBS ${COCOA_LIB} ${IOKIT_LIB} ${COREVIDEO_LIB} ${OPENGL_LIBRARIES} glfw3 pthread)

#platform sources will move to here (when being copied)
FILE(GLOB platform_sources "${VICI_HOME}/Templates/mac/src/*.cpp")

#set and include project sources will be a relative path
include_directories("../../src/")
FILE(GLOB project_sources "../../src/*.cpp")

#compile into a executable
add_executable(MacProject ${platform_sources} ${project_sources})

#link up librares
target_link_libraries(MacProject debug vici ${LIBS})
target_link_libraries(MacProject optimized vici ${LIBS})


#post build commands (copy dlls and their equivilant etc.)

#copy contents of win32 bin folder 
add_custom_command(TARGET MacProject POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${THIRD_PARTY}/bin/mac"
    $<TARGET_FILE_DIR:MacProject>)
	

#copy contents of MacProject to output dir 
add_custom_command(TARGET MacProject POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_directory
    "../../Assets"
    $<TARGET_FILE_DIR:MacProject>/Assets)

add_custom_command(TARGET MacProject POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_directory
    "../../scenes"
    $<TARGET_FILE_DIR:MacProject>/scenes)

add_custom_command(TARGET MacProject POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_directory
    "../../settings"
    $<TARGET_FILE_DIR:MacProject>/settings)