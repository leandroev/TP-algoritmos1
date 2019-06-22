cmake_minimum_required(VERSION 3.5)
project(mi_proyecto)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-pthread")

include_directories(lib/gtest)
include_directories(src/ej1)
include_directories(src/ej2)
include_directories(src/ej3)
add_library(gtest lib/gtest/gtest-all.cc)

add_executable(mi_proyecto
        src/ej1/esPrimo.cpp
        src/ej1/esPrimo.h
        src/ej2/llenarTaxis.cpp
        src/ej2/llenarTaxis.h
        src/ej2/puntaje.cpp
        src/ej2/puntaje.h
        src/ej3/baldosasDelPiso.cpp
        src/ej3/baldosasDelPiso.h
        src/ej3/contandoDragones.cpp
        src/ej3/contandoDragones.h
        src/ej3/sandia.cpp
        src/ej3/sandia.h
        test/ej1/esPrimoTEST.cpp
        test/ej2/llenarTaxisTEST.cpp
        test/ej2/puntajeTEST.cpp
        test/ej3/baldosasDelPisoTEST.cpp
        test/ej3/contandoDragonesTEST.cpp
        test/ej3/sandiaTEST.cpp
        test/correrTests.cpp)


set_target_properties(mi_proyecto PROPERTIES COMPILE_FLAGS "-g --coverage")
set_target_properties(mi_proyecto PROPERTIES LINK_FLAGS "-g --coverage")

target_link_libraries(mi_proyecto gtest)



# Para corre LCOV:
# lcov --capture --directory taller --output-file coverage.info
# genhtml coverage.info --output-directory cobertura
# Y luego abrir la carpeta COBERTURA y explorar los archivos HTML.


