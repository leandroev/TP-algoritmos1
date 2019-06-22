void llenarTaxis1(int g1, int g2, int g3, int& res) {
	res = g3 + (g2 + 1) / 2 + (g1 + 3) / 4;
}

void llenarTaxis2(int g1, int g2, int g3, int& res) {
	res = g3;

	if (g1 <= g3) {
		g1 = 0;
	} else {
		g1 = g1 - g3;
	}

	res = res + (g2 + 1) / 2 + (g1 + 3) / 4;
}

void llenarTaxis3(int g1, int g2, int g3, int& res) {
	res = g3;

	if (g1 <= g3) {
		g1 = 0;
	} else {
		g1 = g1 - g3;
	}

	res = res + g2 / 2;
	if (g2 % 2 == 0) {
		if (g1 >= 2) {
			g1 = g1 - 2;
		} else {
			g1 = 0;
		}
	}

	res = res + (g1 + 3) / 4;
}
