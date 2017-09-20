
BEGIN_MODULE()

set(ADDITIONAL_INCLUDES "")
set(ADDITIONAL_LIB_DIRS "")
set(ADDITONAL_LIBS "")
set(ADDITIONAL_DEPS "")

if(VICI_STANDALONE)
	include(SDL2.cmake)

	set(ADDITIONAL_INCLUDES ${ADDITIONAL_INCLUDES} ${SDL2_INCLUDES})
	set(ADDITIONAL_LIB_DIRS ${ADDITIONAL_LIB_DIRS} ${SDL2_LINK_DIR})
	set(ADDITONAL_LIBS ${ADDITONAL_LIBS} ${SDL2_LIBRARIES})
	set(ADDITIONAL_DEPS ${ADDITIONAL_DEPS} ${SDL2_PROJECT_NAME})
endif()

link_directories(${ADDITIONAL_LIB_DIRS})
#-------------------------------------------------------------------------------------------
# Module Compilation Target
#-------------------------------------------------------------------------------------------
add_library(Platform SHARED ${MODULE_SOURCES})

#-------------------------------------------------------------------------------------------
# Reference other modules. First param is target (i.e. this module)
#-------------------------------------------------------------------------------------------
REF_MODULES(Platform Core)

# Additional Libs & dependencies for this module
target_link_libraries(Platform LINK_PRIVATE ${ADDITONAL_LIBS})
target_include_directories(Platform PRIVATE ${ADDITIONAL_INCLUDES})
add_dependencies(Platform ${ADDITIONAL_DEPS})