#include "../../src/ej1/esPrimo.h"
#include "../../lib/gtest/gtest.h"

TEST(EsPrimoTest, NumeroPrimo) {
	ASSERT_EQ(true, esPrimo(7)); //ES un primo, va adar true
	ASSERT_EQ(true, esPrimo(2)); //idem
}

TEST(EsPrimoTest, NumeroCompuesto) {
	ASSERT_EQ(false, esPrimo(6)); //no es primo, 2,3 6 son divisores
	ASSERT_EQ(false, esPrimo(10)); //idem, con 2,5, y 10
}

TEST(EsPrimoTest, CasosBorde) {
	ASSERT_EQ(false, esPrimo(1)); // no es primo, 1 no tiene dos divisores
	ASSERT_EQ(false, esPrimo(0)); // no es primo
}
