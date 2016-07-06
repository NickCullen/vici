#-------------------------------------------------------------------------------------------
# Source Files
#-------------------------------------------------------------------------------------------
file(GLOB PIL_SOURCES_COMMON 
	# PIL Common
	"*.h"

	# Collections
	"Collections/*.h" 
	"Collections/${VICI_TARGET_SYSTEM}/*.cpp"
	"Collections/${VICI_TARGET_SYSTEM}/*.h"

	# Data types
	"DataTypes/*.h"
	"Collections/${VICI_TARGET_SYSTEM}/*.cpp"
	"Collections/${VICI_TARGET_SYSTEM}/*.h"

	# File System
	"FileSystem/*.h"
	"FileSystem/Common/*.cpp"
	"Collections/${VICI_TARGET_SYSTEM}/*.cpp"
	"Collections/${VICI_TARGET_SYSTEM}/*.h"

	# Graphics
	"Graphics/*.h"
	"Collections/${VICI_TARGET_SYSTEM}/*.cpp"
	"Collections/${VICI_TARGET_SYSTEM}/*.h"

	# Platform 
	"Platform/*.h"
	"Platform/Common/*.cpp"
	"Collections/${VICI_TARGET_SYSTEM}/*.cpp"
	"Collections/${VICI_TARGET_SYSTEM}/*.h"

	# Threads
	"Threads/*.h"
	"Collections/${VICI_TARGET_SYSTEM}/*.cpp"
	"Collections/${VICI_TARGET_SYSTEM}/*.h"

	# Timer
	"Timer/*.h"
	"Collections/${VICI_TARGET_SYSTEM}/*.cpp"
	"Collections/${VICI_TARGET_SYSTEM}/*.h"
)

#-------------------------------------------------------------------------------------------
# Platform specific Source Files
#-------------------------------------------------------------------------------------------
if(VICI_WIN32)
	# Any specific win32 sources can be added here...

elseif(VICI_MAC)
	# Any specific mac sources can be added here...

elseif(VICI_LINUX)
	# Any specific linux sources can be added here...

else()
	set(PLATFORM_SOURCES "")

endif()


#-------------------------------------------------------------------------------------------
# Graphics specific Source Files
#-------------------------------------------------------------------------------------------
if(VICI_OPENGL)
	file(GLOB GRAPHICS_SOURCES 
		# Graphics
		"Graphics/OpenGL/Include/*.h"
		"Graphics/OpenGL/Source/*.cpp"
	)
endif()

#-------------------------------------------------------------------------------------------
# Third Party Includes
#-------------------------------------------------------------------------------------------
if(VICI_WIN32)
	# OpenGL Required
	if(VICI_OPENGL)

		# Glew	----------------------------------------------------------------------
		include_directories("${VICI_THIRD_PARTY_DIR}Glew/Include")

		link_directories("${VICI_THIRD_PARTY_DIR}Glew/Lib/${VICI_TARGET_SYSTEM}/${VICI_PLATFORM_TARGET}")

		# NOTE:: Need to swap glewmxs for glew32 for non-editor builds!
		if(VICI_EDITOR)
			add_definitions(-DGLEW_MX)
			add_definitions(-DGLEW_STATIC)
			set(PIL_LIBRARIES glew32mxs opengl32)
		else()
			set(PIL_LIBRARIES glew32 opengl32)
		endif()

		# End of Glew ----------------------------------------------------------------
	endif()

elseif(VICI_MAC)
	# TODO

elseif(VICI_LINUX)
	# TODO

endif()


#-------------------------------------------------------------------------------------------
# Build to shared library
#-------------------------------------------------------------------------------------------
add_library(PIL SHARED 
	${PIL_SOURCES_COMMON}		# Source files common across all platforms
	${PLATFORM_SOURCES}			# Source files specific to the target platform
	${GRAPHICS_SOURCES}			# Source files specific to the graphics modules
)

if(PIL_LIBRARIES)
	target_link_libraries(PIL PRIVATE ${PIL_LIBRARIES})
endif()