// Matemaattisten luokkien metodien m‰‰rittelyt.
//
// Historia:
// 22.01.2015 Ensimm‰inen versio kirjoitettu. (JL)
// 27.01.2015 Siistitty. (JL)

#include "Math.h"

// Satunnaislukugeneraattorin alustus kellonaikaa k‰ytt‰en.

void initrand()
{
	srand((unsigned) time(NULL));
}

// Satunnainen kokonaisluku x, jolle low <= x <= high.

int randint(int low, int high)
{
	div_t div_result;

	div_result = div(rand(), high - low + 1);
	int rem = div_result.rem;
	int quot = div_result.quot;	// Ei k‰ytet‰.

	return low + rem;
}
