#include "../../src/ej2/llenarTaxis.h"
#include "../../lib/gtest/gtest.h"

// Escribir tests aca:
TEST(llenarTaxisTest, llenarTaxisTest_l_Test) {
    int x;

    llenarTaxis1(2,2,2, x);
    EXPECT_EQ(2, x);

    llenarTaxis2(1,1,1,x);
    EXPECT_EQ(2, x);

    llenarTaxis3(3,1,2,x);
    EXPECT_EQ(3, x);
}

