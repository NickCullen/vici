#-------------------------------------------------------------------------------------------
# Source Files
#-------------------------------------------------------------------------------------------
file(GLOB VICI_EDITOR_EXE_SOURCES 
	LIST_DIRECTORIES false
	RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"

	# Source
	"*.cpp"

)

#-------------------------------------------------------------------------------------------
# Build to shared library
#-------------------------------------------------------------------------------------------
add_executable(ViciEditorLauncher
	${VICI_EDITOR_EXE_SOURCES}	
)

#-------------------------------------------------------------------------------------------
# Modules this library depends upon
#-------------------------------------------------------------------------------------------
target_link_libraries(ViciEditorLauncher PRIVATE PIL Core ViciEditor)



# Filter sources for cleaner project structure
FILTER_SOURCES("${VICI_EDITOR_EXE_SOURCES}")