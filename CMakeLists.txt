cmake_minimum_required(VERSION 3.5)
project(transporteUrbano)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

include(FindSDL2)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)

set(SOURCE_FILES_TEST main.cpp solucion.h solucion.cpp definiciones.h auxiliares.cpp auxiliares.h tests/distanciaAuxTEST.cpp tests/excesoDeVelocidadTEST.cpp tests/tiempoTotalTEST.cpp tests/recorridoNoCubiertoTEST.cpp tests/distanciaTotalTEST.cpp tests/flotaTEST.cpp tests/distanciaAuxTEST.cpp tests/construirGrillaTEST.cpp tests/aPalabraTEST.cpp tests/cantidadDeSaltosTEST.cpp tests/completarHuecosTEST.cpp ejemplos.h)
add_executable(transporteUrbanoTest ${SOURCE_FILES_TEST})

set_target_properties(transporteUrbanoTest PROPERTIES COMPILE_FLAGS "-g --coverage")
set_target_properties(transporteUrbanoTest PROPERTIES LINK_FLAGS "-g --coverage")

target_link_libraries(transporteUrbanoTest gtest gtest_main)

set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
