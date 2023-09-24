#include "../solucion.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

const gps hueco = puntoGps(-1000,-1000);

bool sin_faltantes(viaje v_viaje, vector<int> faltantes){
    for (int i = 0; i < faltantes.size(); ++i) {
        if(obtenerPosicion(v_viaje[faltantes[i]]) == hueco){
            return false;
        }
    }
    return true;
}

int obtener_siguiente_de_hueco(viaje v_viaje, int indice_hueco){
    int index;
    viaje temp = ordenar_viaje(v_viaje);
    for (int i = 1; i < temp.size(); ++i) {
        if(v_viaje[indice_hueco] == temp[i]){
            index = i+1;
            break;
        }
    }
    for (int j = index; j < temp.size(); ++j) {
        if(obtenerPosicion(temp[j]) != hueco){
            index = j;
            break;
        }
    }
    for (int k = 0; k < v_viaje.size() ; ++k) {
        if(obtenerTiempo(v_viaje[k]) == obtenerTiempo(temp[index])){
            index = k;
            break;
        }
    }
    return index;
}

int obtener_anterior_de_hueco(viaje v_viaje, int indice_hueco){
    int index = 0;
    viaje temp = ordenar_viaje(v_viaje);
    for (int i = 1; i < temp.size(); ++i) {
        if(v_viaje[indice_hueco] == temp[i]){
            index = i-1;
            break;
        }
    }
    for (int j = index; j > -1; j--) {
        if(obtenerPosicion(temp[j]) != hueco){
            index = j;
            break;
        }
    }
    for (int k = 0; k < v_viaje.size() ; ++k) {
        if(obtenerTiempo(v_viaje[k]) == obtenerTiempo(temp[index])){
            index = k;
            break;
        }
    }
    return index;
}

bool distancia_y_tiempo_proporcionales(viaje con_huecos, viaje sin_huecos, vector<int> faltantes){
    double proporcion_t;
    gps gps_anterior;
    gps gps_siguiente;
    gps gps_actual;
    tiempo time_siguiente;
    tiempo time_anterior;
    tiempo time_actual;
    int index;
    double dist_anterior;
    double dist_cercanos;
    for (int i = 0; i < faltantes.size(); ++i) {
        index = faltantes[i];
        int cercano_siguiente = obtener_siguiente_de_hueco(con_huecos, index);
        int cercano_anterior = obtener_anterior_de_hueco(con_huecos, index);
        gps_actual = obtenerPosicion(con_huecos[index]);
        time_actual = obtenerTiempo(con_huecos[index]);
        gps_anterior = obtenerPosicion(sin_huecos[cercano_anterior]);
        time_anterior = obtenerTiempo(sin_huecos[cercano_anterior]);
        gps_siguiente = obtenerPosicion(sin_huecos[cercano_siguiente]);
        time_siguiente = obtenerTiempo(sin_huecos[cercano_siguiente]);
        proporcion_t = (time_actual-time_anterior)/(time_siguiente - time_anterior);
        dist_cercanos = distMts(gps_anterior, gps_siguiente)*proporcion_t;
        dist_anterior = distMts(gps_actual, gps_anterior);
        if(dist_cercanos != dist_anterior){
            return false;
        }
    }
    return true;
}

bool sin_huecos(viaje v_viaje){
    for (int i = 0; i < v_viaje.size(); ++i) {
        if(obtenerPosicion(v_viaje[i]) == hueco) {
            return false;
        }
    }
    return true;
}


TEST(completarHuecosTEST, largo_del_viaje_no_cambia){
	gps p1 = puntoGps(-33, -34);
	gps p2 = puntoGps(10, 10);
	gps p3 = puntoGps(0, 0);
    gps p4 = hueco;

	viaje viaje_con_hueco = {medicion(3, p1),
				             medicion(0, p2),
				             medicion(7, p3),
				             medicion(4, p4)
	};

	vector<int> faltantes;
	for (int i = 0; i < viaje_con_hueco.size(); ++i)
	{
		if(obtenerPosicion(viaje_con_hueco[i]) == hueco){
			faltantes.push_back(i);
		}
	}

	viaje viaje_sin_hueco = viaje_con_hueco;
    completarHuecos(viaje_sin_hueco,faltantes);

    EXPECT_EQ(viaje_sin_hueco.size(),viaje_con_hueco.size());
}

TEST(completarHuecosTEST, sin_pos_faltantes){
    gps p1 = puntoGps(-33, -34);
    gps p2 = puntoGps(10, 10);
    gps p3 = hueco;
    gps p4 = hueco;
    gps p5 = hueco;

    viaje viaje_con_huecos = {medicion(9, p1),
                              medicion(1, p2),
                              medicion(7, p3),
                              medicion(4, p4),
                              medicion(2, p5)
    };

    vector<int> faltantes;
    for (int i = 0; i < viaje_con_huecos.size(); ++i)
    {
        if(obtenerPosicion(viaje_con_huecos[i]) == hueco){
            faltantes.push_back(i);
        }
    }

    viaje viaje_sin_huecos = viaje_con_huecos;
    completarHuecos(viaje_sin_huecos,faltantes);

    EXPECT_TRUE(sin_faltantes(viaje_sin_huecos,faltantes));
}

TEST(completarHuecosTEST, puntos_cercanos){
    gps p1 = puntoGps(-33, -34);
    gps p2 = puntoGps(10, 10);
    gps p3 = puntoGps(50,5);
    gps p4 = hueco;
    gps p5 = hueco;

    viaje viaje_con_huecos = {medicion(9, p1),
                              medicion(1, p2),
                              medicion(5, p3),
                              medicion(7, p4),
                              medicion(2, p5)
    };

    vector<int> faltantes;
    for (int i = 0; i < viaje_con_huecos.size(); ++i)
    {
        if(obtenerPosicion(viaje_con_huecos[i]) == hueco){
            faltantes.push_back(i);
        }
    }

    viaje viaje_sin_huecos = viaje_con_huecos;
    completarHuecos(viaje_sin_huecos,faltantes);

    int indice_anterior_tiempo_2 = obtener_anterior_de_hueco(viaje_con_huecos, 4);
    int indice_siguiente_tiempo_2 = obtener_siguiente_de_hueco(viaje_con_huecos, 4);
    int indice_anterior_tiempo_7 = obtener_anterior_de_hueco(viaje_con_huecos, 3);
    int indice_siguiente_tiempo_7 = obtener_siguiente_de_hueco(viaje_con_huecos, 3);
    EXPECT_EQ(indice_anterior_tiempo_2, 1);
    EXPECT_EQ(indice_siguiente_tiempo_2, 2);
    EXPECT_EQ(indice_anterior_tiempo_7, 2);
    EXPECT_EQ(indice_siguiente_tiempo_7, 0);
}

TEST(completarHuecosTEST, proporcional_distancia_y_tiempo){
    gps p1 = puntoGps(-33, -34);
    gps p2 = puntoGps(10, 10);
    gps p3 = puntoGps(50,5);
    gps p4 = hueco;
    gps p5 = hueco;

    viaje viaje_con_huecos = {medicion(9, p1),
                              medicion(1, p2),
                              medicion(5, p3),
                              medicion(7, p4),
                              medicion(2, p5)
    };

    vector<int> faltantes;
    for (int i = 0; i < viaje_con_huecos.size(); ++i)
    {
        if(obtenerPosicion(viaje_con_huecos[i]) == hueco){
            faltantes.push_back(i);
        }
    }

    viaje viaje_sin_huecos = viaje_con_huecos;
    completarHuecos(viaje_sin_huecos,faltantes);

    EXPECT_TRUE(distancia_y_tiempo_proporcionales(viaje_con_huecos, viaje_sin_huecos, faltantes));
}

TEST(completarHuecosTEST, mismos_no_huecos){
    gps p1 = puntoGps(-33, -34);
    gps p2 = puntoGps(10, 10);
    gps p3 = hueco;

    viaje viaje_v = {medicion(9, p1),
                     medicion(1, p2),
                     medicion(5, p3),
    };

    vector<int> faltantes;
    for (int i = 0; i < viaje_v.size(); ++i)
    {
        if(obtenerPosicion(viaje_v[i]) == hueco){
            faltantes.push_back(i);
        }
    }
    completarHuecos(viaje_v, faltantes);
    EXPECT_TRUE(sin_huecos(viaje_v));
}