cmake_minimum_required(VERSION 3.20)
project(C_Collections C)

set(CMAKE_C_STANDARD 99)

add_executable(C_Collections main.c linked_list.h linked_list.c iterator.c iterator.h array_list.h array_list.c collection.c collection.h)
