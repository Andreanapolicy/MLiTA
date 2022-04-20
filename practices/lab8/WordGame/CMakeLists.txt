cmake_minimum_required(VERSION 3.21)
project(WordGame)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS " -static -static-libgcc -static-libstdc++ -std=c++17")

add_executable(WordGame main.cpp)
