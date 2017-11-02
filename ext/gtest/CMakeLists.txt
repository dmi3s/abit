cmake_minimum_required(VERSION 3.9)
project(gtest_builder C CXX)
include(ExternalProject)

ExternalProject_Add(googletest
    URL https://codeload.github.com/google/googletest/zip/release-1.8.0
    URL_MD5 adfafc8512ab65fd3cf7955ef0100ff5
    CMAKE_ARGS -Dgtest_force_shared_crt=ON
               -Dgtest_build_tests=OFF
               -DBUILD_SHARED_LIBS=OFF
               -DLIBRARY_OUTPUT_PATH:PATH=${OUTPUT_DIR}
               ${SPECIAL_EXT_PROJECT_ARGS}

    PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
    UPDATE_COMMAND ""
    PATCH_COMMAND ""
    INSTALL_COMMAND ""
    DOWNLOAD_DIR "${CMAKE_SOURCE_DIR}/.downloaded"
)

# Specify include dir
ExternalProject_Get_Property(googletest source_dir)
set(GTEST_INCLUDE_DIRS ${source_dir}/googletest/include PARENT_SCOPE)

set(GTEST_LIBRARIES
  ${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX}
  ${CMAKE_STATIC_LIBRARY_PREFIX}gtest_main${CMAKE_STATIC_LIBRARY_SUFFIX}
  PARENT_SCOPE
)
