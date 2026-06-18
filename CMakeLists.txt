cmake_minimum_required(VERSION 3.16)
project(AutoPerception VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra)
endif()

# All the project's logic becomes a library — everything in src/ EXCEPT the
# app's entry point, so the same code can back both the app and the tests.
file(GLOB LIB_SOURCES "src/*.cpp")
list(REMOVE_ITEM LIB_SOURCES "${CMAKE_SOURCE_DIR}/src/main.cpp")

add_library(perception ${LIB_SOURCES})
target_include_directories(perception PUBLIC include)

# The application: its entry point, linked against the library.
add_executable(autoperception src/main.cpp)
target_link_libraries(autoperception PRIVATE perception)

# The test runner: its own entry point, linked against the same library.
enable_testing()
add_executable(tests tests/test_main.cpp)
target_link_libraries(tests PRIVATE perception)
add_test(NAME unit_tests COMMAND tests)