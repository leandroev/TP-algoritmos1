
#include "ejercicios.h"

using namespace std;

void programa1(vector<int>& v){
        cout << v[5] << endl;
}
void programaN(vector<int>& v){
    int i = 0;
    while(i < v.size()){
        v[i]++;
        i++;
    }
}
void programaN3(vector<int>& v){
    int i = 0;
    while(i < v.size()){
        hayDuplicados(v);
        i++;
    }
}
void programaNlogN(vector<int>& v){
    int i = v.size()/2;
    i = i+2;
    int buscar = v[i];
    for (int j = 0; j < v.size(); ++j) {
        busqueda_binaria(v,buscar);
    }
}

int main() {
    int i = 1; int n = 10000; int paso = 500 ;
    double tiempo;
    ofstream fout;
    /*double constante;
    int contador = 0;
    fout.open("datos.csv");
    fout << "n\t" << "tiempo" <<endl;
    while(i < n) {
        vector<int> v = construir_vector(i, "asc");
        double t0 = clock();
        hayDuplicados(v);
        double t1 = clock();
        tiempo = (double(t1 - t0) / CLOCKS_PER_SEC);
        constante = tiempo / (i * i);
        fout << i << "\t" << tiempo << endl;
        i +=paso;
        contador++;
    }
    constante = constante/contador;
    cout << "promedio " << constante << endl;

    fout.close();*/
    //Ejercicio 58
    fout.open("datosComplejidad.csv");
    for (int j = 100; j < 100001; j = j*10) {
        vector<int> v = construir_vector(j,"azar");
        double t0 = clock();
        programa1(v);
        double t1 = clock();
        tiempo = (double(t1 - t0) / CLOCKS_PER_SEC);
        fout << tiempo;

        t0 = clock();
        programaN(v);
        t1 = clock();
        tiempo = (double(t1 - t0) / CLOCKS_PER_SEC);
        fout << "\t" << tiempo;

        t0 = clock();
        programaN3(v);
        t1 = clock();
        tiempo = (double(t1 - t0) / CLOCKS_PER_SEC);
        fout << "\t" << tiempo;

        t0 = clock();
        programaNlogN(v);
        t1 = clock();
        tiempo = (double(t1 - t0) / CLOCKS_PER_SEC);
        fout << "\t" << tiempo << endl;
    }
    fout.close();

    return 0;
}
