#include "solucion.h"
#include "auxiliares.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

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
    distancia total = 0;
    for (int i = 1; i < ordenado.size(); ++i) { // ==== >> esto es O(n)
        total += distEnKM(obtenerPosicion(ordenado[i-1]),obtenerPosicion(ordenado[i]));
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

}

/************************************** EJERCICIO construirGrilla *******************************/
grilla construirGrilla(gps esq1, gps esq2, int n, int m) {

}

/***************************************** EJERCICIO aPalabra **********************************/
vector<nombre> aPalabra(recorrido t, grilla g) {

}

/************************************* EJERCICIO cantidadDeSaltos ******************************/
int cantidadDeSaltos(grilla g, viaje v) {

}

//######################### 	Funciones auxiliares 	#####################################\\

viaje ordenarViaje(viaje v){
	int longitud = v.size();
	viaje res;
	tuple<tiempo, gps> elem;
    tiempo temp = 0;
    for (int i = 0; i < longitud; ++i){
        elem = v[i];
		for (int j = 0; j < longitud; ++j){
			if(obtenerTiempo(elem) > obtenerTiempo(v[j]) && obtenerTiempo(v[j]) > temp){
				elem = v[j];
			}
		}
		temp = obtenerTiempo(elem);
		res.push_back(elem);
	}
	return res;
}

double velocidad(tuple<tiempo, gps> t1, tuple<tiempo, gps> t2){
    double dist = distEnKM(obtenerPosicion(t1),obtenerPosicion(t2));
    double time = (obtenerTiempo(t2) - obtenerTiempo(t1))/3600;
    return dist/time;
}