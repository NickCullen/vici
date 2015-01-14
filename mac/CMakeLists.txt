#find required libaries
find_package(OpenGL REQUIRED)

find_library(COCOA_LIB cocoa)
find_library(IOKIT_LIB IOKit)
find_library(COREVIDEO_LIB CoreVideo)

MARK_AS_ADVANCED (COCOA_LIB
                 IOKIT_LIB
                 COREVIDEO_LIB)


message("MESSAGE = ${OPENGL_LIB}")

#include required libraries headers
include_directories(${OPENGL_INCLUDE_DIRS})

#include mac specific headers
include_directories("${CMAKE_CURRENT_LIST_DIR}/include")

#get all mac specific source files
FILE(GLOB sources "src/*.cpp")

#create the platformlib
add_library(platformlib STATIC ${sources})

#set the extra libs so that they will be compiled
set(EXTRA_LIBS ${COCOA_LIB} ${IOKIT_LIB} ${COREVIDEO_LIB} ${OPENGL_LIBRARIES} glfw3 PARENT_SCOPE)
