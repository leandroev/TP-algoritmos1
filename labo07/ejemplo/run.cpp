#include <iostream>
#include "src/runEj.h"
#include "test/runTEST.h"

int main(int argc, char **argv) {
//    runEj();              //arranca el ejemplo directamente
    runTest(argc,argv);     //arranca todos los test
    return 0;
}
