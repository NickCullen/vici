#-------------------------------------------------------------------------------------------
# Source Files
#-------------------------------------------------------------------------------------------
file(GLOB VICI_EDITOR_SOURCES 
	LIST_DIRECTORIES false
	RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"

	# Core
	"*.h"

	# ViciEditor
	"ViciEditor/*.h"
	"ViciEditor/Source/*.cpp"

)

#-------------------------------------------------------------------------------------------
# Definitions
#-------------------------------------------------------------------------------------------
if(VICI_WIN32)
	# OpenGL Required
	if(VICI_OPENGL)
		if(VICI_EDITOR)
			add_definitions(-DGLEW_MX)
		endif()

	endif()

elseif(VICI_MAC)
	# TODO

elseif(VICI_LINUX)
	# TODO

endif()


#-------------------------------------------------------------------------------------------
# Build to shared library
#-------------------------------------------------------------------------------------------
add_library(ViciEditor SHARED
	${VICI_EDITOR_SOURCES}	
)

#-------------------------------------------------------------------------------------------
# Modules this library depends upon
#-------------------------------------------------------------------------------------------
target_link_libraries(ViciEditor PRIVATE PIL Core)


# Filter sources for cleaner project structure
FILTER_SOURCES("${VICI_EDITOR_SOURCES}")

# Create editor EXE
add_subdirectory(ViciEditorLauncher)