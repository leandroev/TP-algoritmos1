#include "../../src/ej/miEjemplo.h"
#include "../../lib/gtest/gtest.h"


TEST(ejTEST1, PotenciaNumEntPosOK_Test ) {
    ASSERT_EQ(8, pot(2,3));
    ASSERT_EQ(9, pot(3,2));
    ASSERT_EQ(27, pot(3,3));
}

TEST(ejTEST2, PotenciaNumFraccPosOK_Test ) {

    EXPECT_EQ (4, pot(16,0.5));
}
TEST(ejTEST2, PotenciaNumRealNegOK_Test ) {

    //EXPECT_EQ (0.00390625, pot(16,-2)); // 0.00390625
    EXPECT_DOUBLE_EQ (0.00390625, pot(16,-2)); // 0.00390625
}
TEST(ejTEST2, PotenciaNumRealNegRangoOK_Test ) {

    EXPECT_NEAR (0.00390, pot(16,-2),0.0001); // 0.00390625    // PASSED
    //EXPECT_NEAR (0.00390, pot(16,-2),0.000001); // 0.00390625  //  FAILED
}

// the Google C++ Testing Framework
// https://github.com/google/googletest/
// https://developer.ibm.com/articles/au-googletestingframework/

//Las ASSERT_*variantes abortan la ejecución del programa si falla una aserción mientras
// , imprime el nombre del archivo, el número de línea y un mensaje que puede personalizar.
/**
 ASSERT_EQ (expected, actual)
 */

// Sería mejor usar las macros específicamente diseñadas para comparaciones
// de punto flotante, cuando las comparaciones sean flotantes.
/**
ASSERT_FLOAT_EQ (expected, actual)
ASSERT_DOUBLE_EQ (expected, actual)
ASSERT_NEAR (expected, actual, absolute_range)

EXPECT_FLOAT_EQ (expected, actual)
EXPECT_DOUBLE_EQ (expected, actual)
EXPECT_NEAR (expected, actual, absolute_range)

*/