cmake_minimum_required (VERSION 3.5)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(UNIX)
    set(Boost_INCLUDE_DIR /usr/include/)
    set(Boost_LIBRARY_DIR /usr/lib/)
endif()

find_package(Boost 1.58 REQUIRED)

project("abit-test" CXX)

set(OUTPUT_DIR ${CMAKE_BINARY_DIR})

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

file(GLOB_RECURSE CALCULATOR_SRCS
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    src/*.cpp
    src/*.hpp
)

add_executable("calculator" ${CALCULATOR_SRCS})

target_sources("calculator" PRIVATE ${CALCULATOR_SRCS})

# MS specific options
if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
    add_definitions(-D_WIN32_WINNT=0x0A00) # Target is windows 10
    target_compile_options("calculator" PUBLIC "/std:c++latest")
    target_compile_options("calculator" PUBLIC "/wd4714")
    target_compile_options("calculator" PUBLIC "/W4")
    target_compile_options("calculator" PUBLIC "/WX")
    target_compile_options("calculator" PUBLIC "/wd4503")
    target_compile_options("calculator" PUBLIC "/MP")
    add_compile_options("$<$<CONFIG:RELASE>:/Zi>")
    #    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
  elseif(UNIX)
    find_package(Threads)
    target_link_libraries("calculator" ${CMAKE_THREAD_LIBS_INIT})
endif()

# DISABLE WITH:  -DBUILD_TESTS=OFF
option (BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
    set(EXT_PROJECTS_DIR ${PROJECT_SOURCE_DIR}/ext)
    add_subdirectory(${EXT_PROJECTS_DIR}/gtest)       # GTEST_INCLUDE_DIRS and GTEST_LIBRARIES
    include_directories(${GTEST_INCLUDE_DIRS})
    link_directories(${OUTPUT_DIR})
    add_subdirectory(tests)
endif()
