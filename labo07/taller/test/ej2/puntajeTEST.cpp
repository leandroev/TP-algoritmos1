#include "../../src/ej2/puntaje.h"
#include "../../lib/gtest/gtest.h"

// Escribir tests aca:
TEST(puntajeTest, puntajeTest_bMenor_Test) {
    ASSERT_EQ(0, puntaje(5));
    ASSERT_EQ(28, puntaje(9)); //
    ASSERT_EQ(22, puntaje(12));
    ASSERT_EQ(1, puntaje(11));
    //idem
}


