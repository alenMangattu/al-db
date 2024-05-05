cmake_minimum_required(VERSION 3.5)
project(client)


find_package(Curses REQUIRED)

add_executable(client client.c loop.c loop.h)
target_link_libraries(client ${CURSES_LIBRARIES})
