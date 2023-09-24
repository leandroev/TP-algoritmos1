#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(flotaTEST, sin_viajes){
    vector<viaje> viajes;
    ASSERT_EQ(flota(viajes,0,10),0);
}

TEST(flotaTEST, viajes_terminaron_antes){
    viaje v1 = {medicion(7.0,puntoGps(0.00001,0.00002)),
               medicion(1.0,puntoGps(0.0,0.0)),
               medicion(4.0,puntoGps(0.00002,0.00001)),
    };
    viaje v2 = {medicion(15.0,puntoGps(0.00001,0.00002)),
               medicion(1.0,puntoGps(0.0,0.0)),
               medicion(10.0,puntoGps(0.00002,0.00001)),
    };
    viaje v3 = {medicion(10.0,puntoGps(0.00001,0.00002)),
               medicion(20.0,puntoGps(0.0,0.0)),
               medicion(8.0,puntoGps(0.00002,0.00001)),
    };
    vector<viaje> viajes={v2,v3,v1};

    ASSERT_EQ(flota(viajes,0.1,0.5),0);
}

TEST(flotaTEST, viaje_comenzaron_tarde){
    viaje v1 = {medicion(7.0,puntoGps(0.00001,0.00002)),
                medicion(1.0,puntoGps(0.0,0.0)),
                medicion(4.0,puntoGps(0.00002,0.00001)),
    };
    viaje v2 = {medicion(15.0,puntoGps(0.00001,0.00002)),
                medicion(1.0,puntoGps(0.0,0.0)),
                medicion(10.0,puntoGps(0.00002,0.00001)),
    };
    viaje v3 = {medicion(10.0,puntoGps(0.00001,0.00002)),
                medicion(20.0,puntoGps(0.0,0.0)),
                medicion(8.0,puntoGps(0.00002,0.00001)),
    };
    vector<viaje> viajes={v3,v2,v1};

    ASSERT_EQ(flota(viajes,90.0,100.0),0);
}

TEST(flotaTEST, todos_los_viajes_en_horario){
    viaje v1 = {medicion(7.0,puntoGps(0.00001,0.00002)),
                medicion(1.0,puntoGps(0.0,0.0)),
                medicion(4.0,puntoGps(0.00002,0.00001)),
    };
    viaje v2 = {medicion(15.0,puntoGps(0.00001,0.00002)),
                medicion(1.0,puntoGps(0.0,0.0)),
                medicion(10.0,puntoGps(0.00002,0.00001)),
    };
    viaje v3 = {medicion(10.0,puntoGps(0.00001,0.00002)),
                medicion(20.0,puntoGps(0.0,0.0)),
                medicion(8.0,puntoGps(0.00002,0.00001)),
    };
    vector<viaje> viajes={v2,v1,v3};

    ASSERT_EQ(flota(viajes,0.1,20.5),3);
}

TEST(flotaTEST, algunos_son_flota){
    viaje v1 = {medicion(7.0,puntoGps(0.00001,0.00002)),
                medicion(1.0,puntoGps(0.0,0.0)),
                medicion(4.0,puntoGps(0.00002,0.00001)),
    };
    viaje v2 = {medicion(15.0,puntoGps(0.00001,0.00002)),
                medicion(1.0,puntoGps(0.0,0.0)),
                medicion(10.0,puntoGps(0.00002,0.00001)),
    };
    viaje v3 = {medicion(10.0,puntoGps(0.00001,0.00002)),
                medicion(20.0,puntoGps(0.0,0.0)),
                medicion(8.0,puntoGps(0.00002,0.00001)),
    };
    viaje v4 = {medicion(10.0,puntoGps(0.00001,0.00002)),
                medicion(12.0,puntoGps(0.0,0.0)),
                medicion(15.0,puntoGps(0.00002,0.00001)),
    };
    vector<viaje> viajes={v2,v1,v4,v3};

    ASSERT_EQ(flota(viajes,11.0,14.5),3);
}

TEST(flotaTEST, viajes_repetidos_cuentan){
    viaje v1 = {medicion(7.0,puntoGps(0.00001,0.00002)),
                medicion(1.0,puntoGps(0.0,0.0)),
                medicion(4.0,puntoGps(0.00002,0.00001)),
    };
    viaje v2 = {medicion(10.0,puntoGps(0.00001,0.00002)),
                medicion(20.0,puntoGps(0.0,0.0)),
                medicion(8.0,puntoGps(0.00002,0.00001)),
    };

    vector<viaje> viajes={v2,v1,v1,v2,v1};

    ASSERT_EQ(flota(viajes,0.1,7.5),3);
}

