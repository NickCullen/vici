#get module sources
FILE(GLOB core "core/*.cpp")
FILE(GLOB rendering "rendering/*.cpp")
FILE(GLOB util "util/*.cpp")
FILE(GLOB datastructures "datastructures/*.cpp")
FILE(GLOB assets "assets/*.cpp")


#get module headers
FILE(GLOB core_h "${VICI_INCLUDES}/core/*.h*")
FILE(GLOB rendering_h "${VICI_INCLUDES}/rendering/*.h*")
FILE(GLOB util_h "${VICI_INCLUDES}/util/*.h*")
FILE(GLOB datastructures_h "${VICI_INCLUDES}/datastructures/*.h*")
FILE(GLOB assets_h "${VICI_INCLUDES}/assets/*.h*")

#group them so visual studio will organise them
source_group("Source\\Core" FILES ${core})
source_group("Header\\Core" FILES ${core_h})
source_group("Source\\Rendering" FILES ${rendering})
source_group("Header\\Rendering" FILES ${rendering_h})
source_group("Source\\Util" FILES ${util})
source_group("Header\\Util" FILES ${util_h})
source_group("Source\\Datastructures" FILES ${datastructures})
source_group("Header\\Datastructures" FILES ${datastructures_h})
source_group("Source\\AssetLoading" FILES ${assets})
source_group("Header\\AssetLoading" FILES ${assets_h})

#do the same with the global engine includes for reference
FILE(GLOB thirdparty_h "${THIRD_PARTY}/*.h*")
source_group("ThirdParty" FILES ${thirdparty_h})

#determine which platform to compile
if(${VICI_WINDOWS})
	#find required libaries
	find_package(OpenGL REQUIRED)

	#include required libraries headers
	include_directories(${OPENGL_INCLUDE_DIRS})

	#include win32 specific headers
	#include_directories("${CMAKE_CURRENT_LIST_DIR}/include")

	#get all windows specific source files
	FILE(GLOB platform_sources "windows/*.cpp")

	#set the extra libs so that they will be compiled
	set(EXTRA_LIBS glfw3 glew32 ${OPENGL_LIBRARIES} PARENT_SCOPE)

	#set the extra libs so that they will be compiled
	set(EXTRA_LIBS_DEBUG vld PARENT_SCOPE)
elseif(${VICI_MAC})

endif()

#compile engine sources
add_library(vlibrary STATIC ${core} ${rendering} ${util} ${datastructures} ${assets} ${platform_sources}
							${core_h} ${rendering_h} ${util_h} ${datastructures_h} ${assets_h} ${thirdparty_h})	#header files need to be included so they get added to the vs filters

