enable_testing()

include_directories(${GTEST_INCLUDE_DIRS})


set(SYM_TABLE_TESTS_SRCS
	src/symtable_tests.cpp
	)

add_executable(symtable_tests ${SYM_TABLE_TESTS_SRCS})

add_dependencies(symtable_tests googletest)
target_link_libraries(symtable_tests ${GTEST_LIBRARIES})
set_target_properties(symtable_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})


set(INTERPRET_TESTS_SRCS
	${PROJECT_SOURCE_DIR}/src/interpret.cpp
        src/interpret_main.cpp
	src/interpret_simple.cpp
	)

add_executable(interpret_tests ${INTERPRET_TESTS_SRCS})
target_link_libraries(interpret_tests ${GTEST_LIBRARIES})
set_target_properties(interpret_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})
