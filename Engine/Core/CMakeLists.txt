#-------------------------------------------------------------------------------------------
# Source Files
#-------------------------------------------------------------------------------------------
file(GLOB CORE_SOURCES 
	LIST_DIRECTORIES false
	RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"

	# Core
	"*.h"

	# Engine
	"Engine/*.h"
	"Engine/Source/*.cpp"

	# Math
	"Math/Math/Include/*.h"
	"Math/Math/Source/*.cpp"

	# Util
	"Util/*.h"
	"Util/Source/*.cpp"
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
add_library(Core SHARED 
	${CORE_SOURCES}	
)

#-------------------------------------------------------------------------------------------
# Modules this library depends upon
#-------------------------------------------------------------------------------------------
target_link_libraries(Core PRIVATE PIL)



# Filter sources for cleaner project structure
FILTER_SOURCES("${CORE_SOURCES}")