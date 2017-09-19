include(ExternalProject)
BEGIN_MODULE()

set(ADDITONAL_LIBS "")

if(VICI_STANDALONE)
	# SDL
	ExternalProject_Add(SDL2_Project
		URL "https://www.libsdl.org/release/SDL2-2.0.5.tar.gz"

		UPDATE_COMMAND ""
		PATCH_COMMAND ""

		SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/SDL2"
		CMAKE_ARGS -DCMAKE_RUNTIME_OUTPUT_DIRECTORY=${CMAKE_RUNTIME_OUTPUT_DIRECTORY} -DCMAKE_LIBRARY_OUTPUT_DIRECTORY=${CMAKE_LIBRARY_OUTPUT_DIRECTORY} -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY=${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}
		
		CMAKE_CACHE_ARGS -DSDL_STATIC:BOOL=OFF -DSDL_SHARED:BOOL=ON

		TEST_COMMAND ""
	)

	ExternalProject_Get_Property(SDL2_Project SOURCE_DIR)
	ExternalProject_Get_Property(SDL2_Project BINARY_DIR)

	set(SDL2_SRC ${SOURCE_DIR})

	message("SDL SRC = ${SDL2_SRC}")
	message("SDL BIN = ${BINARY_DIR}")

	include_directories("${SDL2_SRC}/include")
	message(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
	link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

	if(VICI_WINDOWS)
		set(ADDITONAL_LIBS ${ADDITONAL_LIBS} SDL2)
	else()
		set(ADDITONAL_LIBS ${ADDITONAL_LIBS} SDL2-2.0.1)
	endif()
	
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
