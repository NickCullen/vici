#find required libaries
find_package(OpenGL REQUIRED)

#include required libraries headers
include_directories(${OPENGL_INCLUDE_DIRS})

#include win32 specific headers
include_directories("${CMAKE_CURRENT_LIST_DIR}/include")

#get all windows specific source files
FILE(GLOB sources "src/*.cpp")

#create the platformlib
add_library(platformlib STATIC ${sources})

#set the extra libs so that they will be compiled
set(EXTRA_LIBS glfw3 glew32 ${OPENGL_LIBRARIES} PARENT_SCOPE)
