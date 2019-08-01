cmake_minimum_required(VERSION 3.10)
project(hanoiC C)

set(CMAKE_C_STANDARD 99)


add_executable(hanoiC main.c estado.c estado.h aEstrella.c aEstrella.h monticulo.c monticulo.h)