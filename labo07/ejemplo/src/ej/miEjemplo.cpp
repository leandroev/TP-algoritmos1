#include "miEjemplo.h"
#include<math.h>
double pot (const double num, const double exp){
    double res=0;
    res = pow(num,exp);

    if (num>9999){ // aqui no entra, porque el juego de pruebas no lo contempla
                   // se va a ver en la cobertura que no pudo acceder
        res=1234;
    }
    return res;
}
