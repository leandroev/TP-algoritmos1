#include <iostream>
#include "runEj.h"
#include "ej/miEjemplo.h"

int runEj() {
    double num=16,exp=-2;
    double res = pot(num,exp);
    std::cout << "pot("<<num<<","<<exp<<") = "<<res << std::endl;
    return 0;
}