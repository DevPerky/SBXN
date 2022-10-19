cmake_minimum_required(VERSION 3.10)
project(SBXnative)
set(CMAKE_BUILD_TYPE Debug)


add_subdirectory(dependencies/GLFW)
add_executable(sbxn
    src/main.c
    src/sbx-args.c
    "src/sbxn/sbxn-internal.c"
    src/data-structures/vector.c
    src/data-structures/gen-handle-array.c
)

add_library(test SHARED
    test/test_main.c
)

target_include_directories(sbxn PUBLIC
    src
)

target_include_directories(test PUBLIC
    src/sbxn
)

target_link_libraries(sbxn PUBLIC glfw)