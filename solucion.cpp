#include "solucion.h"
#include "auxiliares.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

//####################################  	Funciones auxiliares 	  ##############################################\\

viaje ordenar_viaje(viaje viaje_original){
    viaje viaje_ordenado = viaje_original;
    int indice_menor_tiempo;
    for (int i = 0; i < viaje_original.size(); ++i){
        indice_menor_tiempo = obtener_indice_menor_tiempo(viaje_ordenado, i, viaje_ordenado.size());
        if(indice_menor_tiempo != i){
            swap_elementos_viaje(viaje_ordenado,i,indice_menor_tiempo);
        }
    }
    return viaje_ordenado;
}

int obtener_indice_menor_tiempo(viaje v_viaje,int desde, int hasta){
    int indice_menor_tiempo = desde; // por la Pre, los viajes no estan vacios, 0 <= desde < hasta < v_viaje.size()
    for (int i = desde; i < hasta; ++i) {
        if(obtenerTiempo(v_viaje[indice_menor_tiempo]) > obtenerTiempo(v_viaje[i])){
            indice_menor_tiempo = i;
        }
    }
    return indice_menor_tiempo;
}

void swap_elementos_viaje(viaje &v_viaje, int indice_1, int indice_2){
    tuple<tiempo, gps> temporal = v_viaje[indice_1];
    v_viaje[indice_1] = v_viaje[indice_2];
    v_viaje[indice_2] = temporal;
}

double velocidad(tuple<tiempo, gps> tiempo_1, tuple<tiempo, gps> tiempo_2){
    double distancia = distEnKM(obtenerPosicion(tiempo_1),obtenerPosicion(tiempo_2));
    double tiempo = (obtenerTiempo(tiempo_2) - obtenerTiempo(tiempo_1))/3600;
    return distancia/tiempo;
}

nombre obtener_nombre_de_gps(gps posicion, grilla g_grilla){
    bool en_celda_latitud;
    bool en_celda_longitud;
    nombre nombre_celda;
    for (int j = 0; j < g_grilla.size(); ++j) {
        gps gps_inf(obtenerEsquinaInferior(g_grilla[j]));
        gps gps_sup(obtenerEsquinaSuperior(g_grilla[j]));
        en_celda_latitud = obtenerLatitud(gps_inf) <= obtenerLatitud(posicion) &&
                           obtenerLatitud(gps_sup) > obtenerLatitud(posicion);
        en_celda_longitud = obtenerLongitud(gps_inf) <= obtenerLongitud(posicion) &&
                            obtenerLongitud(gps_sup) > obtenerLongitud(posicion);
        if(en_celda_latitud && en_celda_longitud){
            nombre_celda = obtenerNombre(g_grilla[j]);
            break;
        }
    }
    return nombre_celda;
}

bool es_cubierto(viaje v_viaje, tiempo inicial, tiempo final){
    bool tiempo_mayor_a_inicial = false;
    bool tiempo_menor_a_final  = false;
    for (int j = 0; j < v_viaje.size(); ++j) {
        if(obtenerTiempo(v_viaje[j]) <= final){
            tiempo_menor_a_final =  true;
        }
        if(obtenerTiempo(v_viaje[j]) >= inicial){
            tiempo_mayor_a_inicial = true;
        }
    }
    if(tiempo_mayor_a_inicial && tiempo_menor_a_final){
        return true;
    }
    return false;
}

int obtener_distancia_nombres(nombre nombre_1,nombre nombre_2){
    int distancia = -1;
    distancia += abs(get<0>(nombre_1) - get<0>(nombre_2)) + abs(get<1>(nombre_1) - get<1>(nombre_2));
    return distancia;
}
//################################################################################################################\\
//################################################################################################################\\

void escribirGrilla(grilla g_grilla, string nombreArchivo){
    ofstream salida_archivo;
    salida_archivo.open(nombreArchivo);
    salida_archivo.setf(ios::fixed);
    salida_archivo.precision(5);
    gps esquina_inferior;
    gps esquina_superior;
    nombre nombre_celda;
    for (int i = 0; i < g_grilla.size(); ++i) {
        esquina_inferior = obtenerEsquinaInferior(g_grilla[i]);
        salida_archivo << obtenerLatitud(esquina_inferior) << "\t";
        salida_archivo << obtenerLongitud(esquina_inferior) << "\t";

        esquina_superior = obtenerEsquinaSuperior(g_grilla[i]);
        salida_archivo << obtenerLatitud(esquina_superior) << "\t";
        salida_archivo << obtenerLongitud(esquina_superior) << "\t";

        nombre_celda = obtenerNombre(g_grilla[i]);
        salida_archivo << "(" << get<0>(nombre_celda) << "," << get<1>(nombre_celda) << ")" << endl;
    }
    salida_archivo.close();
}

void escribirRecorridos(vector<recorrido> recorridos, string nombreArchivo){
    ofstream salida_archivo;
    salida_archivo.open(nombreArchivo);
    salida_archivo.setf(ios::fixed);
    salida_archivo.precision(5);
    recorrido recorrido_actual;
    for (int i = 0; i < recorridos.size(); ++i) {
        recorrido_actual = recorridos[i];
        for (int indice = 0; indice < recorrido_actual.size(); indice++) {
            salida_archivo << i << "\t";
            salida_archivo << obtenerLatitud(recorrido_actual[indice]) << "\t";
            salida_archivo << obtenerLongitud(recorrido_actual[indice]) << endl;
        }
    }
    salida_archivo.close();
}

/*****************************+***** EJERCICIO excesoDeVelocidad **********************************/
bool excesoDeVelocidad(viaje v_viaje) {
    viaje viaje_ordenado = ordenar_viaje(v_viaje);
    for(int i = 1; i < viaje_ordenado.size(); ++i) {
        double vel = velocidad(viaje_ordenado[i-1], viaje_ordenado[i]);
        if(velocidad(viaje_ordenado[i-1], viaje_ordenado[i]) >= 80){
            return true;
        }
    }
    return false;
}

/******++++**************************** EJERCICIO tiempoTotal ***********+++***********************/
tiempo tiempoTotal(viaje v_viaje) {
    tiempo maximo = obtenerTiempo(v_viaje[0]);
    tiempo minimo = maximo;
    for (int i = 1; i < v_viaje.size(); ++i) { // recorro el viaje, n = #elementos del viaje ==> la complejidad es O(n)
        tiempo temporal = obtenerTiempo(v_viaje[i]);
        if(maximo < temporal){
            maximo = temporal;
        }
        if(minimo > temporal){
            minimo = temporal;
        }
    }
    return maximo-minimo;
}

/************++*********************** EJERCICIO distanciaTotal ************++*********************/
distancia distanciaTotal(viaje v_viaje) {
    viaje ordenado = ordenar_viaje(v_viaje);   // === >>  Complejidad = O(n^2)
    distancia total_distancia = 0.0;
    for (int i = 1; i < ordenado.size(); ++i) { // ==== >> Complejidad = O(n)
        total_distancia += abs(distEnKM(obtenerPosicion(ordenado[i-1]),obtenerPosicion(ordenado[i])));
    }
    // Complejidad final ===> O(n) + O(n^2) = O(n^2) 
    return total_distancia;
}

/***************************************** EJERCICIO flota ***************************************/
int flota(vector<viaje> viajes, tiempo inicial, tiempo final) {
    int cantidad_de_flotas = 0;
    viaje viaje_i;
    for (int i = 0; i < viajes.size(); ++i) {
        viaje_i = viajes[i];
        if(es_cubierto(viaje_i,inicial,final)){
            cantidad_de_flotas++;
        }
    }
    return cantidad_de_flotas;
}

/************************************ EJERCICIO recorridoNoCubierto *******************************/
vector<gps> recorridoNoCubierto(viaje v_viaje, recorrido r_recorrido, distancia umbral) {
    vector<gps> puntos_no_cubiertos;
    for (int i = 0; i < r_recorrido.size(); ++i) {
        bool punto_cubierto = false;
        for (int j = 0; j < v_viaje.size(); ++j) {
            if(distMts(obtenerPosicion(v_viaje[j]),r_recorrido[i]) < umbral ){
                punto_cubierto = true;
            }
        }
        if(!punto_cubierto){
            puntos_no_cubiertos.push_back(r_recorrido[i]);
        }
    }
    return puntos_no_cubiertos;
}

/************************************** EJERCICIO construirGrilla *******************************/
grilla construirGrilla(gps esq1, gps esq2, int filas, int columnas) {
    grilla g_grilla;
    double lado_celdas = ((obtenerLatitud(esq2) - obtenerLatitud(esq1)) / filas);
    for (int indice_fila = 1; indice_fila <= filas; indice_fila++) {
        for (int indice_columna = 1; indice_columna <= columnas; indice_columna++) {
            nombre name (indice_fila,indice_columna);
            double latitud_inf = (indice_fila-1)*lado_celdas + obtenerLatitud(esq1);
            double longitud_inf = (indice_columna-1)*lado_celdas + obtenerLongitud(esq1);
            double latitud_sup = (indice_fila)*lado_celdas + obtenerLatitud(esq1);
            double longitud_sup = (indice_columna)*lado_celdas + obtenerLongitud(esq1);
            gps esq_inf = make_tuple(latitud_inf,longitud_inf);
            gps esq_sup = make_tuple(latitud_sup,longitud_sup);
            celda cel = make_tuple(esq_inf, esq_sup, name);
            g_grilla.push_back(cel);
        }
    }
    return  g_grilla;
}

/***************************************** EJERCICIO aPalabra **********************************/
vector<nombre> aPalabra(recorrido trayecto, grilla g_grilla) {
    vector<nombre> secu_nombres;
    for (int i = 0; i < trayecto.size(); ++i) {
        nombre name = obtener_nombre_de_gps(trayecto[i],g_grilla);
        secu_nombres.push_back(name);
    }
    return secu_nombres;
}

/************************************* EJERCICIO cantidadDeSaltos ******************************/
int cantidadDeSaltos(grilla g_grilla, viaje v_viaje) {
    viaje ordenado = ordenar_viaje(v_viaje);
    int numero_de_saltos = 0;
    int distancia_celdas;
    for(int i = 1; i < ordenado.size(); ++i) {
        nombre nombre_1(obtener_nombre_de_gps(obtenerPosicion(ordenado[i-1]),g_grilla));
        nombre nombre_2(obtener_nombre_de_gps(obtenerPosicion(ordenado[i]),g_grilla));
        distancia_celdas = obtener_distancia_nombres(nombre_1,nombre_2);
        if(distancia_celdas > 1){
            numero_de_saltos++;
        }
    }
    return numero_de_saltos;
}
/************************************ Agrego para poder compilar *******************************/
void completarHuecos(viaje& v, vector<int> faltantes){}
