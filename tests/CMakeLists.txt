enable_testing()

include_directories(${GTEST_INCLUDE_DIRS})


file(GLOB SYM_TABLE_TEST_SRCS
	"src/symtable_tests.cpp"
	)

add_executable(symtable_tests ${SYM_TABLE_TEST_SRCS})

add_dependencies(symtable_tests googletest)
target_link_libraries(symtable_tests ${GTEST_LIBRARIES})

set_target_properties(symtable_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

