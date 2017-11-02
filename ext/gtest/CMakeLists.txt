cmake_minimum_required(VERSION 2.8.8)
project(gtest_builder C CXX)
include(ExternalProject)

ExternalProject_Add(googletest
    URL https://github.com/google/googletest/archive/release-1.7.0.zip
    URL_MD5 ef5e700c8a0f3ee123e2e0209b8b4961
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
set(GTEST_INCLUDE_DIRS ${source_dir}/include PARENT_SCOPE)

set(GTEST_LIBRARIES
  ${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX}
  ${CMAKE_STATIC_LIBRARY_PREFIX}gtest_main${CMAKE_STATIC_LIBRARY_SUFFIX}
  PARENT_SCOPE
)
