
BEGIN_MODULE()

#-------------------------------------------------------------------------------------------
# Module Compilation Target
#-------------------------------------------------------------------------------------------
add_library(Platform SHARED ${MODULE_SOURCES})

#-------------------------------------------------------------------------------------------
# Reference other modules. First param is target (i.e. this module)
#-------------------------------------------------------------------------------------------
REF_MODULES(Platform Core)

#-------------------------------------------------------------------------------------------
# Third Party Modules
#-------------------------------------------------------------------------------------------
hunter_add_package(SDL2)

find_package(SDL2 CONFIG REQUIRED)

target_link_libraries(Platform LINK_PRIVATE
	SDL2::SDL2
)

END_MODULE(Platform)