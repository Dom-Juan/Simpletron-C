cmake_minimum_required(VERSION 3.24)
project(Simpletron C)

set(CMAKE_C_STANDARD 23)

add_executable(Simpletron main.c Simpletron_Machine/headers/simpletron_memory.h Simpletron_Machine/simpletron_machine.c Simpletron_Machine/headers/simpletron_machine.h Simpletron_Machine/headers/unistd.h Simpletron_Machine/simpletron_functions.c Simpletron_Machine/headers/simpletron_functions.h)
