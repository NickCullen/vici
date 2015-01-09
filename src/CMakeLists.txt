#get module sources
FILE(GLOB core "core/*.cpp")
FILE(GLOB rendering "rendering/*.cpp")
FILE(GLOB util "util/*.cpp")
FILE(GLOB datastructures "datastructures/*.cpp")

#group them so visual studio will organise them
source_group("core" FILES ${core})
source_group("rendering" FILES ${rendering})
source_group("util" FILES ${util})
source_group("datastructures" FILES ${datastructures})

#compile engine sources
add_library(vlibrary STATIC ${core} ${rendering} ${util} ${datastructures})

