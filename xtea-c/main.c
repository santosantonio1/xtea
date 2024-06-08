#include "src/crypt_xtea.h"

int main()
{	
	// Execute 10 tests
	for(int i=0;i<10;i++)
		crypt_xtea(i);

	return 0;
}