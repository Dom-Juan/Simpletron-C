cmake_minimum_required(VERSION 3.23)
project(Simpletron_C C)

set(CMAKE_C_STANDARD 11)

include_directories(Simpletron/Simpletron_Machine/headers)

add_executable(Simpletron_C
        Simpletron/Simpletron_Machine/headers/simpletron_machine.h
        Simpletron/Simpletron_Machine/headers/simpletron_memory.h
        Simpletron/Simpletron_Machine/headers/unistd.h
        Simpletron/Simpletron_Machine/simpletron_functions.c
        Simpletron/Simpletron_Machine/simpletron_machine.c
        Simpletron/main.c)
