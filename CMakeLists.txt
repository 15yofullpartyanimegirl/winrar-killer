cmake_minimum_required(VERSION 3.10)
project(huffman)

set(CMAKE_CXX_STANDARD 20)

add_executable(zip src/zip.cpp src/huffman.h src/huffman.cpp)
add_executable(unzip src/unzip.cpp src/huffman.h src/huffman.cpp)

