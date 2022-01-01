cmake_minimum_required(VERSION 3.17.3)
project(PROJ_LP C)

set(CMAKE_C_STANDARD 99)

add_executable(PROJ_LP main.c structs.h funct.h cidade.c cidade.h viagem.c viagem.h cliente.c cliente.h)
