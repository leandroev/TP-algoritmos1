#ifndef TRANSPORTEURBANO_SOLUCION_H
#define TRANSPORTEURBANO_SOLUCION_H
#include "definiciones.h"
#include <string>
bool excesoDeVelocidad(viaje v);
tiempo tiempoTotal(viaje v);
distancia distanciaTotal(viaje v);
int flota(vector<viaje> v, tiempo t0, tiempo tf);
vector<gps> recorridoNoCubierto(viaje v, recorrido r, distancia u);
grilla construirGrilla(gps esq1, gps esq2, int n, int m);
vector<nombre> aPalabra(recorrido t, grilla g);
int cantidadDeSaltos(grilla g, viaje v);

//ENTRADA SALIDA
void escribirGrilla(grilla g, string nombreArchivo);
void escribirRecorridos(vector<recorrido> recorridos, string nombreArchivo);

// NO ES NECESARIO IMPLEMENTAR:
void completarHuecos(viaje& v, vector<int> faltantes);

//********* Auxiliares **********
tuple<tiempo, gps> dist_tiempo_proporcional(tuple<tiempo, gps> hueco, tuple<tiempo, gps> anterior,
                                                 tuple<tiempo, gps> siguiente);
int obtener_siguiente_hueco(viaje v_ordenado, viaje v_original, int indice_hueco);
int obtener_anterior_hueco(viaje v_ordenado, viaje v_original, int indice_hueco);
viaje ordenar_viaje(viaje v);
int obtener_indice_menor_tiempo(viaje v, int d, int h);
void swap_elementos_viaje(viaje& v, int i, int j);
double velocidad(tuple<tiempo, gps> t1, tuple<tiempo, gps> t2);
nombre obtener_nombre_de_gps(gps posicion, grilla g_grilla);
bool es_cubierto(viaje v, tiempo inicial, tiempo final);

#endif //TRANSPORTEURBANO_SOLUCION_H
