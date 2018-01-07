project(Example)

add_executable(Example main.cpp)

include_directories(../include)

target_link_libraries(Example
    CodeExecutor
    dl
    stdc++fs
)