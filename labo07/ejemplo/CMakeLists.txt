cmake_minimum_required(VERSION 3.5)        #version de cmake
project(Ejemplo)                            #crea el proyecto "Ejemplo"

set(CMAKE_CXX_STANDARD 14)                  #habilita el estandar 14 de c++
set(CMAKE_CXX_FLAGS "-pthread")             #bandera para activar pthrea

include_directories(lib/gtest)              #incluye directorio con librerias de gtest
add_library(gtest lib/gtest/gtest-all.cc)   #incluye la libreria de gtest...

include_directories(src)                    #incluye directorio con codigo fuente de aplicacion
include_directories(src/ej)

include_directories(test)                   #incluye directorio con codigo de los TEST de prueba
include_directories(test/ej)

add_executable(Ejemplo                      #incluye el codigo fuente
        run.cpp

        src/runEj.cpp
        src/runEj.h

        src/ej/miEjemplo.cpp
        src/ej/miEjemplo.h

        test/runTEST.cpp
        test/runTEST.h

        test/ej/ejTEST.cpp

        )


set_target_properties(Ejemplo PROPERTIES COMPILE_FLAGS "-g --coverage")
set_target_properties(Ejemplo PROPERTIES LINK_FLAGS "-g --coverage")

target_link_libraries(Ejemplo gtest)