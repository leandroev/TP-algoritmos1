#include "solucion.h"
#include "auxiliares.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

//############################  	Funciones auxiliares 	  #####################################\\

viaje ordenarViaje(viaje v){
    viaje res;
    tiempo tiempo_anterior = -1;
    tuple<tiempo, gps> actual;
    for (int i = 0; i < v.size(); ++i){
        actual = v[0];
        for (int j = 0; j < v.size(); ++j) {
            if( obtenerTiempo(actual) < obtenerTiempo(v[j]) && obtenerTiempo(actual) <= tiempo_anterior || obtenerTiempo(actual) > obtenerTiempo(v[j]) && obtenerTiempo(v[j]) > tiempo_anterior){
                actual = v[j];
            }
        }
        tiempo_anterior = obtenerTiempo(actual);
        res.push_back(actual);
    }
    return res;
}

double velocidad(tuple<tiempo, gps> t1, tuple<tiempo, gps> t2){
    double dist = distEnKM(obtenerPosicion(t1),obtenerPosicion(t2));
    double time = (obtenerTiempo(t2) - obtenerTiempo(t1))/3600;
    return dist/time;
}

nombre obtenerNombreDeGps(gps posicion, grilla g){
    for (int j = 0; j < g.size(); ++j) {
        gps gps_inf(obtenerEsquinaInferior(g[j]));
        gps gps_sup(obtenerEsquinaSuperior(g[j]));
        bool esCeldaDeCoordenada = obtenerLatitud(gps_inf) <= obtenerLatitud(posicion) && obtenerLatitud(posicion) < obtenerLatitud(gps_sup) && obtenerLongitud(gps_inf) <= obtenerLongitud(posicion) && obtenerLongitud(posicion) < obtenerLongitud(gps_sup);
        if(esCeldaDeCoordenada){
            return obtenerNombre(g[j]);
        }
    }
}

// #######################################################################################################################################################################################################
void escribirGrilla(grilla g, string nombreArchivo){

}

void escribirRecorridos(vector<recorrido> recorridos, string nombreArchivo){

}

/*****************************+***** EJERCICIO excesoDeVelocidad **********************************/
bool excesoDeVelocidad(viaje v) {
    viaje ordenado = ordenarViaje(v);
    for(int i = 1; i < ordenado.size(); ++i) {
        if(velocidad(ordenado[i-1], ordenado[i]) >= 80){
            return true;
        }
    }
    return false;
}

/******++++**************************** EJERCICIO tiempoTotal ***********+++***********************/
tiempo tiempoTotal(viaje v) {
    tiempo maximo = obtenerTiempo(v[0]);
    tiempo minimo = maximo;
    for (int i = 1; i < v.size(); ++i) {        // === >>  esto es O(n)
        tiempo temp = obtenerTiempo(v[i]);
        if(maximo < temp){
            maximo = temp;
        }
        if(minimo > temp){
            minimo = temp;
        }
    }
    return maximo-minimo;
}

/************++*********************** EJERCICIO distanciaTotal ************++*********************/
distancia distanciaTotal(viaje v) {
    viaje ordenado = ordenarViaje(v);   // === >>  esto es O(n^2)
    distancia total = 0.0;
    for (int i = 1; i < ordenado.size(); ++i) { // ==== >> esto es O(n)
        total += abs(distEnKM(obtenerPosicion(ordenado[i-1]),obtenerPosicion(ordenado[i])));
    }
    // ==== O(n) + O(n^2) = O(n^2)
    return total;
}

/***************************************** EJERCICIO flota ***************************************/
int flota(vector<viaje> f, tiempo t0, tiempo tf) {
    int viajes = 0;
    for (int i = 0; i < f.size(); ++i) {
        viaje v = f[i];
        bool menor = false;
        bool mayor = false;
        for (int j = 0; j < v.size(); ++j) {
            if(obtenerTiempo(v[j]) <= tf){
                mayor =  true;
            }
            if(obtenerTiempo(v[j]) >= t0){
                menor = true;
            }
        }
        if(mayor && menor){
            viajes++;
        }
    }
    return viajes;
}

/************************************ EJERCICIO recorridoCubierto *******************************/
vector<gps> recorridoNoCubierto(viaje v, recorrido r, distancia u) {
    vector<gps> no_cubiertos;
    for (int i = 0; i < r.size(); ++i) {
    	bool cubierto = false;
        for (int j = 0; j < v.size(); ++j) {
            if(distMts(obtenerPosicion(v[j]),r[i]) < u ){
                cubierto = true;
            }
        }
        if(!cubierto){
        	no_cubiertos.push_back(r[i]);
        }
    }
    return no_cubiertos;
}

/************************************** EJERCICIO construirGrilla *******************************/
grilla construirGrilla(gps esq1, gps esq2, int n, int m) {
    grilla g;
    int lado = (obtenerLatitud(esq2) - obtenerLatitud(esq1))/n;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            nombre name(i,j);
            gps esq_inf((i-1)*lado + obtenerLatitud(esq1),(j-1)*lado + obtenerLongitud(esq1));
            gps esq_sup((i)*lado + obtenerLatitud(esq1),(j)*lado + obtenerLongitud(esq1));
            celda cel(esq_inf, esq_sup, name);
            g.push_back(cel);
        }
    }
    return  g;
}

/***************************************** EJERCICIO aPalabra **********************************/
vector<nombre> aPalabra(recorrido t, grilla g) {
    vector<nombre> secu_nombres;
    for (int i = 0; i < t.size(); ++i) {
        nombre name = obtenerNombreDeGps(t[i],g);
        secu_nombres.push_back(name);
    }
    return secu_nombres;
}

/************************************* EJERCICIO cantidadDeSaltos ******************************/
int cantidadDeSaltos(grilla g, viaje v) {
    viaje ordenado = ordenarViaje(v);
    int saltos = 0;
    for(int i = 1; i < ordenado.size(); ++i) {
        nombre n1(obtenerNombreDeGps(obtenerPosicion(ordenado[i-1]),g));
        nombre n2(obtenerNombreDeGps(obtenerPosicion(ordenado[i]),g));
        int distancia_celdas = abs(get<0>(n1) - get<0>(n2)) + abs(get<1>(n1) - get<1>(n2)) -1;
        if(distancia_celdas > 1){
            saltos++;
        }
    }
}

