include(ExternalProject)
BEGIN_MODULE()

set(ADDITONAL_LIBS "")

if(VICI_STANDALONE)
	# SDL
	ExternalProject_Add(SDL2_Project
		URL "https://www.libsdl.org/release/SDL2-2.0.5.tar.gz"
		INSTALL_COMMAND ""
		CMAKE_CACHE_ARGS -DSDL_STATIC:BOOL=OFF
	)

	ExternalProject_Get_Property(SDL2_Project SOURCE_DIR)
	ExternalProject_Get_Property(SDL2_Project BINARY_DIR)

	set(SDL2_SRC ${SOURCE_DIR})
	set(SDL2_BIN ${BINARY_DIR})

	message("SDL SRC = ${SDL2_SRC}")
	message("SDL BIN = ${SDL2_BIN}")
	
	include_directories("${SDL2_SRC}/include")
	link_directories("${SDL2_BIN}")

	set(ADDITONAL_LIBS ${ADDITONAL_LIBS} SDL2-2.0)
endif()

#-------------------------------------------------------------------------------------------
# Module Compilation Target
#-------------------------------------------------------------------------------------------
add_library(Platform SHARED ${MODULE_SOURCES})

#-------------------------------------------------------------------------------------------
# Reference other modules. First param is target (i.e. this module)
#-------------------------------------------------------------------------------------------
REF_MODULES(Platform Core)

# Additional libs for this module.
target_link_libraries(Platform LINK_PRIVATE ${ADDITONAL_LIBS})
add_dependencies(Platform SDL2_Project)