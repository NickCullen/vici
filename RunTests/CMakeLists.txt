#-------------------------------------------------------------------------------------------
# References all test modules (passed in from parent)
#-------------------------------------------------------------------------------------------
set(TEST_SOURCES "")
foreach(MOD ${TEST_MODULES})
    message("TESTING ${MOD} @ ${${MOD}_LOCATION}")

    file( GLOB_RECURSE TEST_FILES              # Variable containing all source files      
        "${${MOD}_LOCATION}Tests/*.*"             # Relative paths from the root directory
    )
    set(TEST_SOURCES ${TEST_SOURCES} ${TEST_FILES})
endforeach()

#-------------------------------------------------------------------------------------------
# Creates an executable called "RunTests" which will reference all modules 
# and include the google test framework
#-------------------------------------------------------------------------------------------
add_executable(RunTests main.cpp ${TEST_SOURCES})

REF_MODULES(RunTests ${TEST_MODULES})

#-------------------------------------------------------------------------------------------
# Ensure Google Test framework is included and linked for all following targets.
#-------------------------------------------------------------------------------------------
hunter_add_package(GTest)   
find_package(GTest CONFIG REQUIRED) 
target_link_libraries(RunTests LINK_PRIVATE GTest::gtest)