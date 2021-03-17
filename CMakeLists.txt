# cmake_minimum_required(VERSION <specify CMake version here>)
project(sa2021 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(sa2021
        03.practical.work.shell.c
        04.practical.work.shell.signal.c
        07.practical.work.shell.pipe.c)
