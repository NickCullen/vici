#-------------------------------------------------------------------------------------------
# Source Files
#-------------------------------------------------------------------------------------------
file(GLOB CORE_SOURCES 
	# Core
	"*.h"

	# Engine
	"Engine/*.h"
	"Engine/Source/*.cpp"

	# Math
	"Engine/*.h"
	"Engine/Source/*.cpp"

	# Util
	"Engine/*.h"
	"Engine/Source/*.cpp"
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
