cmake_minimum_required(VERSION 3.5)

project(StateMachine)

add_definitions(-Weverything -Wno-c++98-compat -Wno-padded -Wno-class-varargs -Wno-exit-time-destructors -Wnon-pod-varargs)

# add_executable(Examples src/examples.cpp)
# set_target_properties(Examples
#   PROPERTIES
#     CXX_STANDARD          14
#     CXX_STANDARD_REQUIRED YES
#     CXX_EXTENSIONS        NO
# )



add_executable(TestRunner src/unittests.cpp)

target_link_libraries(TestRunner)


set_target_properties(TestRunner
  PROPERTIES
    CXX_STANDARD          14
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS        NO
)

enable_testing()

add_test(NAME unittests COMMAND ./TestRunner)
