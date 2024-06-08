#include <stdio.h>
#include <stdint.h>

#define ENC 1
#define DEC 0

//-----------------------------------------------------------------------------
// XTEA: 128-bits
//-----------------------------------------------------------------------------
void xtea_enc(unsigned int **dest, const unsigned int **v, const unsigned int **k);
void xtea_dec(unsigned int **dest, const unsigned int **v, const unsigned int **k);
void xtea(unsigned int* key, unsigned int* input, unsigned int *output, char encript);

//-----------------------------------------------------------------------------
// Main Function
//-----------------------------------------------------------------------------
int crypt_xtea(int);