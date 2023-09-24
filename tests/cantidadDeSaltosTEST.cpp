#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(cantidadDeSaltosTEST, viaje_sin_ordenar_sin_saltos) {
    gps esq1 = puntoGps(0, 15);
    gps esq2 = puntoGps(90, 150);
    grilla g = construirGrilla(esq1, esq2, 2, 3);
// grilla_esq_inf = (1,1)=(0,15), (1,2)=(0,60), (1,3)=(0,105), (2,1)=(45,15), (2,2)=(45,60), (2,3)=(45,105)
// grilla_esq_sup = (1,1)=(45,60), (1,2)=(45,105), (1,3)=(45,150), (2,1)=(90,60), (2,2)=(90,105), (2,3)=(90,150)

    recorrido trayecto = {puntoGps(20, 15),
                          puntoGps(60, 30),
                          puntoGps(80, 130),
                          puntoGps(30, 110),
    };

    viaje v;
    vector<int> desorden_viaje = {3,2,0,5};
    for (int j = 0; j < trayecto.size() ; ++j) {
        v.push_back(medicion(desorden_viaje[j],trayecto[j]));
    }

    vector<nombre> nombres = aPalabra(trayecto, g); //{(2,3),(2,1),(1,1),(1,3)}
    ASSERT_EQ(cantidadDeSaltos(g,v),0);
}

TEST(cantidadDeSaltosTEST, viaje_sin_ordenar_con_saltos) {
    gps esq1 = puntoGps(0, 15);
    gps esq2 = puntoGps(90, 150);
    grilla g = construirGrilla(esq1, esq2, 2, 3);
// grilla_esq_inf = (1,1)=(0,15), (1,2)=(0,60), (1,3)=(0,105), (2,1)=(45,15), (2,2)=(45,60), (2,3)=(45,105)
// grilla_esq_sup = (1,1)=(45,60), (1,2)=(45,105), (1,3)=(45,150), (2,1)=(90,60), (2,2)=(90,105), (2,3)=(90,150)

    recorrido trayecto = {puntoGps(20, 15),
                          puntoGps(60, 30),
                          puntoGps(80, 130),
                          puntoGps(30, 110),
    };

    viaje v;
    vector<int> desorden_viaje = {3,0,5,2};
    for (int j = 0; j < trayecto.size() ; ++j) {
        v.push_back(medicion(desorden_viaje[j],trayecto[j]));
    }

    vector<nombre> nombres = aPalabra(trayecto, g); //<(2,1),(1,3),(1,1),(2,3)>

    ASSERT_EQ(cantidadDeSaltos(g,v),2);
}


TEST(cantidadDeSaltosTEST, viaje_ordenado_sin_saltos) {
    gps esq1 = puntoGps(0, 15);
    gps esq2 = puntoGps(90, 150);
    grilla g = construirGrilla(esq1, esq2, 2, 3);
// grilla_esq_inf = (1,1)=(0,15), (1,2)=(0,60), (1,3)=(0,105), (2,1)=(45,15), (2,2)=(45,60), (2,3)=(45,105)
// grilla_esq_sup = (1,1)=(45,60), (1,2)=(45,105), (1,3)=(45,150), (2,1)=(90,60), (2,2)=(90,105), (2,3)=(90,150)

    recorrido trayecto = {puntoGps(20, 15),
                          puntoGps(60, 30),
                          puntoGps(80, 130),
                          puntoGps(30, 110),
    };

    viaje v;
    for (int j = 0; j < trayecto.size() ; ++j) {
        v.push_back(medicion(j,trayecto[j]));
    }

    vector<nombre> nombres = aPalabra(trayecto, g); //{(1,1),(2,1),(2,3),(1,3)};
    ASSERT_EQ(cantidadDeSaltos(g,v),0);
}

TEST(cantidadDeSaltosTEST, viaje_ordenado_con_saltos) {
    gps esq1 = puntoGps(0, 15);
    gps esq2 = puntoGps(90, 150);
    grilla g = construirGrilla(esq1, esq2, 2, 3);
// grilla_esq_inf = (1,1)=(0,15), (1,2)=(0,60), (1,3)=(0,105), (2,1)=(45,15), (2,2)=(45,60), (2,3)=(45,105)
// grilla_esq_sup = (1,1)=(45,60), (1,2)=(45,105), (1,3)=(45,150), (2,1)=(90,60), (2,2)=(90,105), (2,3)=(90,150)

    recorrido trayecto = {puntoGps(60, 30),
                          puntoGps(30, 110),
                          puntoGps(20, 15),
                          puntoGps(80, 130)
    };

    viaje v;
    for (int j = 0; j < trayecto.size() ; ++j) {
        v.push_back(medicion(j,trayecto[j]));
    }

    vector<nombre> nombres = aPalabra(trayecto, g); //<(2,1),(1,3),(1,1),(2,3)>
    ASSERT_EQ(cantidadDeSaltos(g,v),2);
}