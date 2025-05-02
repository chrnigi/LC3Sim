cmake_minimum_required(VERSION 3.15)

add_executable(lc3app src/appMain.c)
target_link_libraries(lc3app lc3)