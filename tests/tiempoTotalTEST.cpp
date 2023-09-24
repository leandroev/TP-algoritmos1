#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(tiempoTotalTEST, viaje_desordenado){
    viaje v = {medicion(7.0,puntoGps(0.00001,0.00002)),
               medicion(1.0,puntoGps(0.0,0.0)),
               medicion(4.0,puntoGps(0.00002,0.00001)),
               medicion(6.3,puntoGps(0.00004,0.00011))
    };

    ASSERT_DOUBLE_EQ(tiempoTotal(v), 6.0);
}

TEST(tiempoTotalTEST, viaje_ordenado){
    viaje v = {medicion(1.0,puntoGps(0.0,0.0)),
               medicion(4.0,puntoGps(0.00002,0.00001)),
               medicion(6.3,puntoGps(0.00004,0.00011)),
               medicion(7.0,puntoGps(0.00001,0.00002))
    };

    ASSERT_DOUBLE_EQ(tiempoTotal(v),6.0);
}

TEST(tiempoTotalTEST, viaje_parado){
    viaje v = {medicion(1.0,puntoGps(0.0,0.1)),
               medicion(4.0,puntoGps(0.0,0.1))
    };
    ASSERT_DOUBLE_EQ(tiempoTotal(v),3.0);
}

TEST(tiempoTotalTEST, viaje_ida_y_vuelta){
    viaje v = {medicion(1.0,puntoGps(0.0,0.0)),
               medicion(6.3,puntoGps(0.00004,0.00011)),
               medicion(7.0,puntoGps(0.0,0.0)),
    };
    ASSERT_DOUBLE_EQ(tiempoTotal(v),6.0);
}