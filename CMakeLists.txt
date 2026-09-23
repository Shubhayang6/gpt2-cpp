cmake_minimum_required(VERSION 3.18) #3.18+ required for CUDA
project(gpt-cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON) # Fails if the compiler doesn't see C++17
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(gpt2 src/main.cpp)

if(MSVC)
    target_compile_options(gpt2 PRIVATE /W4 /permissive-)
else()
    target_compile_options(gpt2 PRIVATE -Wall -Wextra -Wpedantic)
endif()
