#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;


TEST(excesoDeVelocidadTEST, viaje_normal_desordenado){
    viaje v = {medicion(7.0,puntoGps(0.00001,0.00002)),
               medicion(1.0,puntoGps(0.0,0.0)),
               medicion(4.0,puntoGps(0.00002,0.00001)),
               medicion(6.3,puntoGps(0.00004,0.00011))
    };

    ASSERT_FALSE(excesoDeVelocidad(v));
}

TEST(excesoDeVelocidadTEST, viaje_normal_ordenado){
    viaje v = {medicion(1.0,puntoGps(0.0,0.0)),
               medicion(4.0,puntoGps(0.00002,0.00001)),
               medicion(6.3,puntoGps(0.00004,0.00011)),
               medicion(7.0,puntoGps(0.00001,0.00002))
    };

    ASSERT_FALSE(excesoDeVelocidad(v));
}

TEST(excesoDeVelocidadTEST, viaje_rapido_desordenado){
    viaje v = {medicion(7.0,puntoGps(0.00001,0.00002)),
               medicion(1.0,puntoGps(1.0,0.0)),
               medicion(4.0,puntoGps(0.00002,0.00001)),
               medicion(6.3,puntoGps(1.002,0.0041))
    };
    ASSERT_TRUE(excesoDeVelocidad(v));
}

TEST(excesoDeVelocidadTEST, viaje_rapido_ordenado){
    viaje v = {medicion(1.0,puntoGps(0.0,0.0)),
               medicion(4.0,puntoGps(0.00002,0.00001)),
               medicion(6.3,puntoGps(1.002,0.0041)),
               medicion(7.0,puntoGps(0.00001,0.00002))
    };
    ASSERT_TRUE(excesoDeVelocidad(v));
}