#get module sources
FILE(GLOB core "core/*.cpp")
FILE(GLOB rendering "rendering/*.cpp")
FILE(GLOB util "util/*.cpp")
FILE(GLOB datastructures "datastructures/*.cpp")
FILE(GLOB assets "assets/*.cpp")

#get module headers
FILE(GLOB core_h "${VICI_INCLUDES}/core/*.h*")
FILE(GLOB rendering_h "${VICI_INCLUDES}/rendering/*.h*")
FILE(GLOB util_h "${VICI_INCLUDES}/util/*.h*")
FILE(GLOB datastructures_h "${VICI_INCLUDES}/datastructures/*.h*")
FILE(GLOB assets_h "${VICI_INCLUDES}/assets/*.h*")

#group them so visual studio will organise them
source_group("Source\\Core" FILES ${core})
source_group("Header\\Core" FILES ${core_h})
source_group("Source\\Rendering" FILES ${rendering})
source_group("Header\\Rendering" FILES ${rendering_h})
source_group("Source\\Util" FILES ${util})
source_group("Header\\Util" FILES ${util_h})
source_group("Source\\Datastructures" FILES ${datastructures})
source_group("Header\\Datastructures" FILES ${datastructures_h})
source_group("Source\\AssetLoading" FILES ${assets})
source_group("Header\\AssetLoading" FILES ${assets_h})


#do the same with the global engine includes for reference
FILE(GLOB include_h "${PROJECT_SOURCE_DIR}/include/*.h*")
source_group("Includes" FILES ${include_h})

#compile engine sources
add_library(vlibrary STATIC ${core} ${rendering} ${util} ${datastructures} ${assets}
							${core_h} ${rendering_h} ${util_h} ${datastructures_h} ${assets_h} ${include_h})	#header files need to be included so they get added to the vs filters

