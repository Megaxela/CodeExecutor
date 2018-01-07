cmake_minimum_required(VERSION 3.8)
project(CodeExecutor)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_subdirectory(example)

add_library(CodeExecutor
        src/CodeExecutor/Builder.cpp
        include/CodeExecutor/Builder.hpp
        src/CodeExecutor/Compiler.cpp
        include/CodeExecutor/Compiler.hpp
        src/CodeExecutor/Linker.cpp
        include/CodeExecutor/Linker.hpp
        src/CodeExecutor/Object.cpp
        include/CodeExecutor/Object.hpp
        src/CodeExecutor/Source.cpp
        include/CodeExecutor/Source.hpp
        include/CodeExecutor/filesystem.hpp
        src/CodeExecutor/BuildingContext.cpp
        include/CodeExecutor/BuildingContext.hpp
        src/CodeExecutor/Library.cpp
        include/CodeExecutor/Library.hpp
        src/CodeExecutor/Process.cpp
        include/CodeExecutor/Process.hpp
)