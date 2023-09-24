#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(aPalabraTEST, trayecto_vacio){
    gps esq1 = puntoGps(0,15);
    gps esq2 = puntoGps(90,150);
    grilla g = construirGrilla(esq1,esq2,10,15);

    recorrido trayecto;
    vector<nombre> nombres = aPalabra(trayecto, g);
    ASSERT_EQ(nombres.size(), 0);
}

TEST(aPalabraTEST, trayecto_de_enteros){
    gps esq1 = puntoGps(0,15);
    gps esq2 = puntoGps(90,150);
    grilla g = construirGrilla(esq1,esq2,2,3);
    // grilla_esq_inf = (1,1)=(0,15), (1,2)=(0,60), (1,3)=(0,105), (2,1)=(45,15), (2,2)=(45,60), (2,3)=(45,105)
    // grilla_esq_sup = (1,1)=(45,60), (1,2)=(45,105), (1,3)=(45,150), (2,1)=(90,60), (2,2)=(90,105), (2,3)=(90,150)

    double alto_celda = (get<0>(esq2) - get<0>(esq1))/2;
    double ancho_celda = (get<1>(esq2) - get<1>(esq1))/3;
    ASSERT_DOUBLE_EQ(alto_celda, ancho_celda);

    recorrido trayecto = {puntoGps(20,15),
                          puntoGps(60,30),
                          puntoGps(80,130),
                          puntoGps(65,100),
                          };

    vector<nombre> nombres = aPalabra(trayecto, g);
    vector<nombre> nombres_esperado = {make_tuple(1,1),make_tuple(2,1),make_tuple(2,3),make_tuple(2,2)};
    ASSERT_EQ(nombres,nombres_esperado);
}

