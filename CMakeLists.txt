cmake_minimum_required(VERSION 3.26)
project(projetVersion2 C)

set(CMAKE_C_STANDARD 11)

add_executable(main main.c projet.c)

# Activer l'option de compilation AVX pour l'exécutable 'main'
target_compile_options(main PRIVATE -mavx)