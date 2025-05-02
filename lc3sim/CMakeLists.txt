cmake_minimum_required(VERSION 3.15)

add_library(lc3 src/LC3.c src/operations.c include/LC3.h include/operations.h)

target_include_directories(lc3 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")