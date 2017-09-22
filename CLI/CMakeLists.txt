set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${VICI_HOME}CLI/Bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${VICI_HOME}CLI/Lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${VICI_HOME}CLI/Lib")

hunter_add_package(Boost COMPONENTS program_options)
find_package(Boost CONFIG REQUIRED program_options)
link_libraries(Boost::program_options)

add_executable(vici main.cpp)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Commands/")

add_subdirectory(HeaderTool)

