#-------------------------------------------------------------------------------------------
# Global Options
#-------------------------------------------------------------------------------------------
option(VICI_WITH_TESTS "Include test framework (Google Test), if true sources in Tests folder will be included" ON)
option(VICI_EDITOR_BUILD "Is this an editor build?" ON)

#-------------------------------------------------------------------------------------------
# Module Helper Macros
#-------------------------------------------------------------------------------------------
# Appens to the module list
macro(_Internal_APPEND_MODULE MOD_NAME)
	if( NOT DEFINED MODULE_LIST)
		set(MODULE_LIST "")
	endif()

	set(MODULE_LIST ${MODULE_LIST} ${MOD_NAME} )
endmacro(_Internal_APPEND_MODULE)

# Must be set at start of module
macro(BEGIN_MODULE)
	# Required Include folders
	include_directories("Include")

	# Source/Header file management (for pretty solution files)
	#-------------------------------------------------------------------------------------------
	file( GLOB_RECURSE MOD_SRC_FILES              # Variable containing all source files
		LIST_DIRECTORIES false                      
		RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/"             # Relative paths from the root directory
		"Source/*.cpp"                              # Search pattern
	)

	file( GLOB_RECURSE MOD_HEADER_FILES              # Variable containing all source files
		LIST_DIRECTORIES false                      
		RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/"             # Relative paths from the root directory
		"Include/*.h"                              # Search pattern
	)

	set(VALID_SOURCES "")
	set(VALID_HEADERS "")

	# Remove any files which shouldn't be in this build.
	foreach(ITEM ${MOD_SRC_FILES})
		# Standalone builds.
		if(NOT VICI_STANDALONE)
			if("${ITEM}" MATCHES "/Standalone/")
				message("Excluding ${ITEM} as this is not a Standalone build.")
				continue()
			endif()
		endif()

		# Windows builds
		if(NOT VICI_WINDOWS)
			if("${ITEM}" MATCHES "/Windows/")
				message("Excluding ${ITEM} as this is not a Windows build.")
				continue()
			endif()
		endif()

		# Mac builds
		if(NOT VICI_MAC)
			if("${ITEM}" MATCHES "/Mac/")
				message("Excluding ${ITEM} as this is not a Mac build.")
				continue()
			endif()
		endif()

		# Linux builds
		if(NOT VICI_LINUX)
			if("${ITEM}" MATCHES "/Linux/")
				message("Excluding ${ITEM} as this is not a Linux build.")
				continue()
			endif()
		endif()

		# Valid if it gets here
		set(VALID_SOURCES ${VALID_SOURCES} ${ITEM})
	endforeach()

	# Remove any files which shouldn't be in this build.
	foreach(ITEM ${MOD_HEADER_FILES})
		# Standalone builds.
		if(NOT VICI_STANDALONE)
			if("${ITEM}" MATCHES "/Standalone/")
				message("Excluding ${ITEM} as this is not a Standalone build.")
				continue()
			endif()
		endif()

		# Windows builds
		if(NOT VICI_WINDOWS)
			if("${ITEM}" MATCHES "/Windows/")
				message("Excluding ${ITEM} as this is not a Windows build.")
				continue()
			endif()
		endif()

		# Mac builds
		if(NOT VICI_MAC)
			if("${ITEM}" MATCHES "/Mac/")
				message("Excluding ${ITEM} as this is not a Mac build.")
				continue()
			endif()
		endif()

		# Linux builds
		if(NOT VICI_LINUX)
			if("${ITEM}" MATCHES "/Linux/")
				message("Excluding ${ITEM} as this is not a Linux build.")
				continue()
			endif()
		endif()

		# Valid if it gets here
		set(VALID_HEADERS ${VALID_HEADERS} ${ITEM})
	endforeach()

	# Run filter on source/headers
	FILTER_SOURCES("${VALID_SOURCES}")
	FILTER_SOURCES("${VALID_HEADERS}")
	set(MODULE_SOURCES ${VALID_SOURCES} ${VALID_HEADERS})
	
endmacro(BEGIN_MODULE)

macro(END_MODULE TAR)
	
endmacro()

# To be placed for each module in each project folders DeclModules.cmake file
macro(DECL_MODULE MOD_NAME MOD_LOC)
	message("DECL_MODULE: ${MOD_NAME} at ${MOD_LOC}")
	set("${MOD_NAME}_LOCATION" "${MOD_LOC}")
	set("${MOD_NAME}_INCLUDES_LOC" "${MOD_LOC}Include")

	set("${MOD_NAME}_BINARIES_LOC" "${CMAKE_SOURCE_DIR}/${RUNTIME_FOLDER_PATH}")
	set("${MOD_NAME}_LIB_LOC" "${CMAKE_SOURCE_DIR}/${LIBRARY_FOLDER_PATH}")

	# Append to module list
	_Internal_APPEND_MODULE(${MOD_NAME})
endmacro(DECL_MODULE)

# For engine modules to be declared
macro(DECL_ENGINE_MODULE MOD_NAME MOD_LOC)
	message("DECL_ENGINE_MODULE: ${MOD_NAME} at ${MOD_LOC}")
	set("${MOD_NAME}_LOCATION" "${MOD_LOC}")
	set("${MOD_NAME}_INCLUDES_LOC" "${MOD_LOC}Include")

	set("${MOD_NAME}_BINARIES_LOC" "${VICI_RUNTIME_FOLDER}")
	set("${MOD_NAME}_LIB_LOC" "${VICI_LIBRARY_FOLDER}")

	# Append to module list
	_Internal_APPEND_MODULE(${MOD_NAME})
endmacro(DECL_ENGINE_MODULE)

# References all specified modules for TAR (target)
macro(REF_MODULES TAR)
	message("${TAR} Is refernecing:")
	foreach(MOD ${ARGN})
		message("-- ${MOD}")
		target_include_directories(${TAR} PRIVATE "${${MOD}_INCLUDES_LOC}")
		link_directories("${${MOD}_LIB_LOC}/")
		target_link_libraries(${TAR} LINK_PRIVATE ${MOD})
		add_dependencies(${TAR} ${MOD})
	endforeach()
endmacro(REF_MODULES)

# Ensure all shared library objects exist. Should be called
# when the target is an executable and all .dlls are required
macro(COPY_MODULE_SHARED_OBJECTS TAR)
	foreach(MOD ${MODULE_LIST})
		if(NOT "${MOD}" STREQUAL "${TAR}")
			add_custom_command(TARGET ${TAR} POST_BUILD 
				COMMAND ${CMAKE_COMMAND} -E copy_directory
				"${${MOD}_BINARIES_LOC}"
				$<TARGET_FILE_DIR:${TAR}>)
		endif()
	endforeach()
endmacro(COPY_MODULE_SHARED_OBJECTS)

#-------------------------------------------------------------------------------------------
# Helpful Functions / Macros
#-------------------------------------------------------------------------------------------
function(FILTER_SOURCES SOURCE_LIST)
	foreach(_source IN ITEMS ${SOURCE_LIST})
		get_filename_component(_source_path "${_source}" PATH)

		if(VICI_WINDOWS)
			string(REPLACE "/" "\\" _source_path "${_source_path}")
		endif()

		source_group("${_source_path}" FILES "${_source}")
	endforeach()
endfunction()

#-------------------------------------------------------------------------------------------
# Defines
#-------------------------------------------------------------------------------------------
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-DVICI_ENGINE)

# Common Defines
if(${CMAKE_SIZEOF_VOID_P} EQUAL 8)
	message("64 Bit build")
	add_definitions(-DVICI_64BIT)
	set(VICI_64BIT 1)
else()
	message("32 bit build")
	add_definitions(-DVICI_32BIT)
	set(VICI_32BIT 1)
endif()

# Editor build or not?
if(VICI_EDITOR_BUILD)
	add_definitions(-DVICI_EDITOR)
	set(VICI_EDITOR 1)
endif()

# Windows Defines
if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	message("Windows Build")

	add_definitions(-DVICI_WINDOWS)
	add_definitions(-DVICI_WIN32)
	add_definitions(-DVICI_STANDALONE)
	set(VICI_WINDOWS 1)
	set(VICI_WIN32 1)
	set(VICI_STANDALONE 1)

	# Set these so we can traverse the correct folders easily
	set(VICI_TARGET_SYSTEM "Windows")
	if(VICI_32BIT)
		set(VICI_PLATFORM_TARGET "x86")
	else()
		set(VICI_PLATFORM_TARGET "x64")
	endif()

# Mac Defines
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
	message("Mac Build")

	add_definitions(-DVICI_MAC)
	add_definitions(-DVICI_STANDALONE)
	set(VICI_MAC 1)
	set(VICI_STANDALONE 1)

	# Set these so we can traverse the correct folders easily
	set(VICI_TARGET_SYSTEM "Mac")
	if(VICI_32BIT)
		set(VICI_PLATFORM_TARGET "x86")
	else()
		set(VICI_PLATFORM_TARGET "x64")
	endif()

# Linux Defines
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
	message("Linux Build")

	add_definitions(-DVICI_LINUX)
	add_definitions(-DVICI_STANDALONE)
	set(VICI_LINUX 1)
	set(VICI_STANDALONE 1)

	# Set these so we can traverse the correct folders easily
	set(VICI_TARGET_SYSTEM "Linux")
	if(VICI_32BIT)
		set(VICI_PLATFORM_TARGET "x86")
	else()
		set(VICI_PLATFORM_TARGET "x64")
	endif()
endif()


#-------------------------------------------------------------------------------------------
# Compiler Flags
#-------------------------------------------------------------------------------------------
if(NOT VICI_WINDOWS )
	set(CMAKE_CXX_STANDARD 14)
	set(CMAKE_CXX_FLAGS "-std=c++14 ${CMAKE_CXX_FLAGS}")
endif()

#-------------------------------------------------------------------------------------------
# Generic output locations
# Paths here are relative to whatever absolute folder is being specified so that
# there is a consistent bin/lib output folder wherever you prefix with.
#-------------------------------------------------------------------------------------------
if(VICI_EDITOR)
	set(RUNTIME_FOLDER_PATH "Binaries/${VICI_TARGET_SYSTEM}/Runtime/Editor")
	set(LIBRARY_FOLDER_PATH "Binaries/${VICI_TARGET_SYSTEM}/Lib/Editor")
	set(ARCHIVE_FOLDER_PATH "Binaries/${VICI_TARGET_SYSTEM}/Lib/Editor")
else()
	set(RUNTIME_FOLDER_PATH "Binaries/${VICI_TARGET_SYSTEM}/Runtime")
	set(LIBRARY_FOLDER_PATH "Binaries/${VICI_TARGET_SYSTEM}/Lib")
	set(ARCHIVE_FOLDER_PATH "Binaries/${VICI_TARGET_SYSTEM}/Lib")
endif()

set(VICI_RUNTIME_FOLDER "${VICI_HOME}/${RUNTIME_FOLDER_PATH}")
set(VICI_LIBRARY_FOLDER "${VICI_HOME}/${LIBRARY_FOLDER_PATH}")
set(VICI_ARCHIVE_FOLDER "${VICI_HOME}/${ARCHIVE_FOLDER_PATH}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/${RUNTIME_FOLDER_PATH}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/${LIBRARY_FOLDER_PATH}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/${ARCHIVE_FOLDER_PATH}")

#-------------------------------------------------------------------------------------------
# Declare All Engine Modules
#-------------------------------------------------------------------------------------------
include("${VICI_HOME}Engine/DeclModules.cmake")