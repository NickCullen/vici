set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${VICI_HOME}CLI/Bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${VICI_HOME}CLI/Lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${VICI_HOME}CLI/Lib")

add_executable(vici main.cpp)

hunter_add_package(Boost COMPONENTS program_options)
find_package(Boost CONFIG REQUIRED program_options)
target_link_libraries(vici Boost::program_options)
