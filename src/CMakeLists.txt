#get module sources
FILE(GLOB core "core/*.cpp")
FILE(GLOB rendering "rendering/*.cpp")
FILE(GLOB util "util/*.cpp")
FILE(GLOB datastructures "datastructures/*.cpp")

#get module headers
FILE(GLOB core_h "core/*.h*")
FILE(GLOB rendering_h "rendering/*.h*")
FILE(GLOB util_h "util/*.h*")
FILE(GLOB datastructures_h "datastructures/*.h*")

#group them so visual studio will organise them
source_group("Source\\Core" FILES ${core})
source_group("Header\\Core" FILES ${core_h})
source_group("Source\\Rendering" FILES ${rendering})
source_group("Header\\Rendering" FILES ${rendering_h})
source_group("Source\\Util" FILES ${util})
source_group("Header\\Util" FILES ${util_h})
source_group("Source\\Datastructures" FILES ${datastructures})
source_group("Header\\Datastructures" FILES ${datastructures_h})

#compile engine sources
add_library(vlibrary STATIC ${core} ${rendering} ${util} ${datastructures} 
							${core_h} ${rendering_h} ${util_h} ${datastructures_h} )	#header files need to be included so they get added to the vs filters

