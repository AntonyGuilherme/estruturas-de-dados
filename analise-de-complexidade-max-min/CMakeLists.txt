cmake_minimum_required(VERSION 3.19)
project(analise_de_complexidade_max_min)

set(CMAKE_CXX_STANDARD 14)

add_executable(analise_de_complexidade_max_min main.cpp FuncaoDeComplexidade/analise-de-complexidade.cpp TecnicasDeAnalise/TecnicasDeAnalise.cpp TecnicasDeAnalise/AlgoritmoDeSelecao.c)