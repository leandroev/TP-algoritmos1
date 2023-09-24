#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(construirGrillaTEST, grilla_1x1){
    gps esq1 = puntoGps(-90, -50);
    gps esq2 = puntoGps(0, 40);
    grilla g = construirGrilla(esq1, esq2, 1, 1);

    double alto_celda = (get<0>(esq2) - get<0>(esq1)) / 1;
    double ancho_celda = (get<1>(esq2) - get<1>(esq1)) / 1;
    ASSERT_DOUBLE_EQ(alto_celda, ancho_celda);
    ASSERT_EQ(g.size(),1);
}

TEST(construirGrillaTEST, varias_celdas) {
    gps esq1 = puntoGps(0, 15);
    gps esq2 = puntoGps(90, 150);
    grilla g = construirGrilla(esq1, esq2, 10, 15);

    double alto_celda = (get<0>(esq2) - get<0>(esq1)) / 2;
    double ancho_celda = (get<1>(esq2) - get<1>(esq1)) / 3;
    ASSERT_DOUBLE_EQ(alto_celda, ancho_celda);
    ASSERT_EQ(g.size(),150);
}

TEST(construirGrilla, pocas_celdas) {
    gps esq1 = puntoGps(0, 15);
    gps esq2 = puntoGps(90, 150);
    grilla g = construirGrilla(esq1, esq2, 2, 3);

    double alto_celda = (get<0>(esq2) - get<0>(esq1)) / 2;
    double ancho_celda = (get<1>(esq2) - get<1>(esq1)) / 3;
    ASSERT_DOUBLE_EQ(alto_celda, ancho_celda);
    ASSERT_EQ(g.size(),6);
}

TEST(construirGrillaTEST, interseccion_esq_sup_con_esq_inf) {
    gps esq1 = puntoGps(0, 15);
    gps esq2 = puntoGps(90, 150);
    grilla g = construirGrilla(esq1, esq2, 10, 15);

    double lado_celda = (get<0>(esq2) - get<0>(esq1)) / 10;

    bool esquinas_validas = true;
    for (int i = 1; i < g.size(); ++i) {
        gps esq_inf_anterior = obtenerEsquinaInferior(g[i-1]);
        gps esq_sup_anterior = obtenerEsquinaSuperior(g[i-1]);
        gps esq_inf_actual = obtenerEsquinaInferior(g[i]);
        gps esq_sup_actual = obtenerEsquinaSuperior(g[i]);

        if(obtenerLatitud(esq_inf_actual) != (obtenerLatitud(esq_inf_anterior)+lado_celda) ){
            bool esquinas_validas = false;
            break;
        }
        if(obtenerLongitud(esq_inf_actual) != (obtenerLongitud(esq_inf_anterior)+lado_celda) ){
            bool esquinas_validas = false;
            break;
        }
        if(obtenerLatitud(esq_sup_actual) != (obtenerLatitud(esq_sup_anterior)+lado_celda) ){
            bool esquinas_validas = false;
            break;
        }
        if(obtenerLongitud(esq_sup_actual) != (obtenerLongitud(esq_sup_anterior)+lado_celda) ){
            bool esquinas_validas = false;
            break;
        }
    }
    ASSERT_TRUE(esquinas_validas);
}
