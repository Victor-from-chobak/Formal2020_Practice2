cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE  ON)
add_compile_options(-std=c++1z)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(OBJECT_DIR ${CMAKE_BINARY_DIR}/CMakeFiles/run_tests.dir)
message("-- FILES WILL BE HERE: ${OBJECT_DIR}")

set(SOURCES_TESTS
    test.cpp
    Algo.cpp
    Grammar.cpp
    )

add_executable(run_tests ${SOURCES_TESTS})

add_custom_target(code_coverage 
    COMMAND mkdir -p coverage
    COMMAND ${CMAKE_MAKE_PROGRAM} test
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )

add_custom_command(TARGET code_coverage
    COMMAND echo "======== THIS IS RESULTS OF TESTS COVERAGE ========" "\n"
    COMMAND gcov -b ${CMAKE_SOURCE_DIR}/Algo.cpp ${CMAKE_SOURCE_DIR}/test.cpp -o ${OBJECT_DIR}
    | egrep -A 5 '/Algo.cpp|/Grammar.cpp' > CoverageSummary.tmp
    COMMAND echo "Algo.cpp coverage " "\n"
    COMMAND sed '2,5!d' CoverageSummary.tmp
    COMMAND echo "=== THATS ALL ===" "\n"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/coverage
    )

add_dependencies(code_coverage run_tests)

target_link_libraries(run_tests ${GTEST_LIBRARIES} pthread)

enable_testing()

add_test(COVERAGE_TEST ${CMAKE_CURRENT_BINARY_DIR}/run_tests)


set(SOURCES_SOLVER
    main.cpp
    Algo.cpp
    Grammar.cpp
    )

add_executable(task_solver ${SOURCES_SOLVER})
