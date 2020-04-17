#include "MMATH.H"
#include "PolynomUtilities.h"
#include "PolynomsLib_Bin_1.H"
#include <iostream>


void add_polynom(M_LONG a, M_LONG b, M_LONG res) {
	DIGIT* maxLenPol, * minLenPol;
	int maxLen, minLen;

	if (a[0] > b[0]) {
		maxLenPol = a; maxLen = a[0];
		minLenPol = b; minLen = b[0];
	} else {
		maxLenPol = b; maxLen = b[0];
		minLenPol = a; minLen = a[0];
	}

	for (int i = 1; i <= minLen; i++)
		res[i] = minLenPol[i] ^ maxLenPol[i];
	
	for (int i = minLen + 1; i <= maxLen; i++)
		res[i] = maxLenPol[i];
	
	res[0] = maxLen;
}

void mulmod_polynom(M_LONG a, M_LONG b, M_LONG mod, M_LONG res) {
	res[0] = mod[0];
	int mod_bit = degree(mod) % 32;
	int mod_word = mod[0];

	if (mod_bit == 1)
		res[0]--;

	memset(&res[1], 0, (res[0] + 1) * 4);
	M_LONG buf = { 0 };
	m_copy(buf, a);

	for (int i = 1; i <= b[0]; i++)	{
		for (int j = 0; j < 32; j++) {
			if ((b[i] >> j) & 1)
				add_polynom(res, buf, res);

			m_shl(buf, 1);

			if ((buf[mod_word] >> mod_bit) & 1)
				add_polynom(mod, buf, buf);
		}
	}

	while (res[res[0]] == 0 && res[0] > 1)
		res[0]--;
}


void mulmod_polynom_comb(M_LONG a, M_LONG b, M_LONG mod, M_LONG res) {
	M_LONG precalculation[16];
	precalculation[0][0] = 1; precalculation[0][1] = 0;
	M_LONG buf = { 1, 0 };

	for (int i = 1; i < 16; i++) {
		buf[1] = i;
		mulmod_polynom(b, buf, mod, precalculation[i]);
	}

	memset(&res[1], 0, mod[0] * 8);

	for (int k = 7; k >= 0; k--) {
		res[0] = mod[0] * 2;

		for (int i = 1; i <= a[0]; i++) {
			unsigned int u = (a[i] >> (k * 4)) & 0xf;

			for (int l = i, j = 1; j <= precalculation[u][0]; j++, l++)
				res[l] ^= precalculation[u][j];
		}

		if (k != 0)
			m_shl(res, 4);
		rem_pol(res, mod);
	}

	while (res[res[0]] == 0 && res[0] > 1)
		res[0]--;
}

int test_mulmod_comb(int n)
{
	int errors = 0;
	M_LONG a, b, mod, result_lib, result_my_func;

	for (int i = 0; i < n + 1; i++)	{
		m_rand(mod, 16);
		m_rand(a, 12);
		m_rand(b, 12);

		mulmod_pol(a, b, mod, result_lib);
		mulmod_polynom_comb(a, b, mod, result_my_func);

		if (m_cmp(result_lib, result_my_func))
			errors++;

		// printing for debug
		if (i % 100 == 0 and i != 0)
			cout << "Test #" << i << "; Amount of errors: " << errors << endl;

	}
	return errors;
}

int main() {
	int test_samples = 5000;
	cout << "Test samples: " << test_samples << endl;

	int number_of_errors = test_mulmod_comb(test_samples);

    cout << number_of_errors << " errors in comb-multiplication method" << endl;
	return 0;
}
