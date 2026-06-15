cmake_minimum_required(VERSION 3.16)
project(AutoPerception VERSION 1.0 LANGUAGES CXX)

# Use C++17, and require it
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Turn on common warnings
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra)
endif()

# Gather every .cpp in src/ as the program's sources
file(GLOB SOURCES "src/*.cpp")

# Build one executable called "autoperception" from those sources
add_executable(autoperception ${SOURCES})

# Tell the compiler where the headers live
target_include_directories(autoperception PRIVATE include)