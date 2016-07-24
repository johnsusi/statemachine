set(CMAKE_SYSTEM_NAME Darwin)

set(CMAKE_C_COMPILER          "clang"          CACHE STRING "C compiler"          FORCE)
set(CMAKE_CXX_COMPILER        "clang++"        CACHE STRING "C++ compiler"        FORCE)
set(CMAKE_CXX_FLAGS           "-stdlib=libc++" CACHE STRING "Compile flags"       FORCE)
set(CMAKE_EXE_LINKER_FLAGS    "-stdlib=libc++" CACHE STRING "Linker flags"        FORCE)
set(CMAKE_SHARED_LINKER_FLAGS "-stdlib=libc++" CACHE STRING "Shared linker flags" FORCE)
