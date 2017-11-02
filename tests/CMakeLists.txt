enable_testing()
#find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})


file(GLOB SYM_TABLE_TEST_SRCS
	"src/symtable_test.cpp"
	)

add_executable(symtable_test ${SYM_TABLE_TEST_SRCS})

add_dependencies(symtable_test googletest)
target_link_libraries(symtable_test ${GTEST_LIBRARIES})

set_target_properties(symtable_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

