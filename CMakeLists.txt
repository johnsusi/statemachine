cmake_minimum_required(VERSION 3.6)

project(StateMachine)

add_executable(TestRunner src/unittests.cpp)

set_target_properties(TestRunner
  PROPERTIES
    CXX_STANDARD          14
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS        NO
)

enable_testing()

add_test(NAME unittests COMMAND ./TestRunner)
