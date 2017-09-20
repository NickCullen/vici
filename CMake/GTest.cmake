include(ExternalProject)

set(GTEST_PROJECT_NAME GTest_Project)

# Google Test
ExternalProject_Add(${GTEST_PROJECT_NAME}
    GIT_REPOSITORY "https://github.com/google/googletest"

    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    INSTALL_COMMAND ""
    
    SOURCE_DIR "${VICI_HOME}ThirdParty/GoogleTest"
    CMAKE_ARGS -DBUILD_SHARED_LIBS:BOOL=ON -DCMAKE_RUNTIME_OUTPUT_DIRECTORY=${VICI_RUNTIME_FOLDER} -DCMAKE_LIBRARY_OUTPUT_DIRECTORY=${VICI_LIBRARY_FOLDER} -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY=${VICI_ARCHIVE_FOLDER}

    CMAKE_CACHE_ARGS -DCMAKE_DEBUG_POSTFIX:STRING=""

    TEST_COMMAND ""
)

ExternalProject_Get_Property(${GTEST_PROJECT_NAME} SOURCE_DIR)
ExternalProject_Get_Property(${GTEST_PROJECT_NAME} BINARY_DIR)

set(GTEST_SRC_DIR ${SOURCE_DIR})
set(GTEST_BIN_DIR ${BINARY_DIR})

set(GTEST_INCLUDES "${GTEST_SRC_DIR}/googletest/include" "${GTEST_SRC_DIR}/googlemock/include")
set(GTEST_LINK_DIR "${VICI_LIBRARY_FOLDER}")

if(VICI_WINDOWS)
    set(GTEST_LIBRARIES gtest gmock)
else()
    set(GTEST_LIBRARIES gtest gmock)
endif()


message("----- ThirdParty: GTEST -----")
message("Include Dir: ${GTEST_INCLUDES}")
message("Link Dir: ${GTEST_LINK_DIR}")
message("Libraries: ${GTEST_LIBRARIES}")
message("----------------------------")
