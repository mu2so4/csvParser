cmake_minimum_required(VERSION 3.21)
project(super_csv)

set(CMAKE_CXX_STANDARD 14)

add_executable(super_csv main.cpp tuple_io.h parser.h)
