cmake_minimum_required(VERSION 3.8)
project(CodeExecutorTests)

if (EXISTS ${CMAKE_CURRENT_LIST_DIR}/benchmark/CMakeLists.txt)
    add_subdirectory(googletest)
endif()

add_executable(CodeExecutorTests
        main.cpp
        Building.cpp)

target_link_libraries(CodeExecutorTests
        CodeExecutor
        gtest
        dl
)