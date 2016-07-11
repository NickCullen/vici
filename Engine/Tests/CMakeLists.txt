#-------------------------------------------------------------------------------------------
# Source Files
#-------------------------------------------------------------------------------------------
file(GLOB SOURCE_LIST 
	LIST_DIRECTORIES false
	RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"

	# All
	"*.h"
	"*.cpp"
)



#-------------------------------------------------------------------------------------------
# Build to shared library
#-------------------------------------------------------------------------------------------
add_executable(Tests ${SOURCE_LIST})

#-------------------------------------------------------------------------------------------
# Modules this library depends upon
#-------------------------------------------------------------------------------------------
target_link_libraries(Tests PRIVATE PIL Core)

if(VICI_EDITOR)
target_link_libraries(Tests PRIVATE ViciEditor)
endif()

# Filter sources for cleaner project structure
FILTER_SOURCES("${SOURCE_LIST}")