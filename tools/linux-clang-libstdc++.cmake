set(CMAKE_SYSTEM_NAME Linux)

set(CMAKE_C_COMPILER          "clang"                                  CACHE STRING "C compiler"          FORCE)
set(CMAKE_CXX_COMPILER        "clang++"                                CACHE STRING "C++ compiler"        FORCE)
set(CMAKE_CXX_FLAGS           "-stdlib=libstdc++ -Wno-non-pod-varargs" CACHE STRING "Compile flags"       FORCE)
set(CMAKE_EXE_LINKER_FLAGS    "-stdlib=libstdc++"                      CACHE STRING "Linker flags"        FORCE)
set(CMAKE_SHARED_LINKER_FLAGS "-stdlib=libstdc++"                      CACHE STRING "Shared linker flags" FORCE)
