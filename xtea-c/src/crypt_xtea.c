#include "crypt_xtea.h"

// Numbers
int tests_n[10][4] = {
    {0x546cf7be,0xe2cd9a9b,0x2213ba3c,0x9a23039e},
    {0x2E4D1C1C,0x82D7AEED,0xE97C851A,0x7809F717},
    {0x11719bd1,0x74f1087b,0xece3337b,0xdb45799f},
    {0x3224F131,0x7B44CBA0,0xB053D945,0xD3BD3F40},
    {0xc5b3f4ab,0x3ca0b22f,0x5fed902f,0xf7f42b32},
    {0xB89A56EC,0xEF0D3242,0x53B8BEAB,0x154F605F},
    {0x16943fbf,0x12575dd8,0x306acfd6,0xd3567ae8},
    {0x0c01e919,0xf60329a9,0x0e09c248,0x87f7e7d5},
    {0x63bc22b8,0x3100fe86,0x5e090607,0x24c19bcd},
    {0x6a542539,0x305ba527,0x87308195,0xb5d5a372}
};

// Keys
int tests_k[10][4] = {
    {0xd4a4fa0a,0x7288d343,0x9590753e,0x4fc6ab97},
    {0xd4a4fa0a,0x7288d343,0x9590753e,0x4fc6ab97},
    {0x09733c35,0xdd770b57,0x0cd5ee5a,0x81969e24},
    {0x09733c35,0xdd770b57,0x0cd5ee5a,0x81969e24},
    {0xd49d2bcd,0x2d8edc36,0x9dd71ce8,0x701babc6},
    {0xd49d2bcd,0x2d8edc36,0x9dd71ce8,0x701babc6},
    {0x6bd63f02,0x97458e6b,0x64be6baa,0x5c19ae3c},
    {0xd53e01d1,0x575a94d1,0xd2572ef5,0x61988afa},
    {0x9b012e1b,0x3bf30209,0xf5e7221f,0xe773893c},
    {0x39043367,0xb7d15b35,0xe083d860,0x41834a86}
};

// Config
//     1 - ENC
//     0 - DEC
int tests_c[10] = {1,0,1,0,1,0,0,1,1,0};

//-----------------------------------------------------------------------------
// XTEA: 128-bits
//-----------------------------------------------------------------------------
void xtea_enc(unsigned int **dest, const unsigned int **v, const unsigned int **k) {
    char i;
    unsigned int y0 = *v[0], z0 = *v[1], y1 = *v[2], z1 = *v[3];
    unsigned int sum = 0, delta = 0x9E3779B9;

    for(i = 0; i < 32; i++) {
        y0  += ((z0 << 4 ^ z0 >> 5) + z0) ^ (sum + *k[sum & 3]);
        y1  += ((z1 << 4 ^ z1 >> 5) + z1) ^ (sum + *k[sum & 3]);
        sum += delta;
        z0  += ((y0 << 4 ^ y0 >> 5) + y0) ^ (sum + *k[sum>>11 & 3]);
        z1  += ((y1 << 4 ^ y1 >> 5) + y1) ^ (sum + *k[sum>>11 & 3]);
    }
    *dest[0]=y0; *dest[1]=z0; *dest[2]=y1; *dest[3]=z1;
}

void xtea_dec(unsigned int **dest, const unsigned int **v, const unsigned int **k) {
    char i;
    unsigned int y0 = *v[0], z0 = *v[1], y1 = *v[2], z1 = *v[3];
    unsigned int sum = 0xC6EF3720, delta = 0x9E3779B9;
    for(i = 0; i < 32; i++) {
        z1  -= ((y1 << 4 ^ y1 >> 5) + y1) ^ (sum + *k[sum>>11 & 3]);
        z0  -= ((y0 << 4 ^ y0 >> 5) + y0) ^ (sum + *k[sum>>11 & 3]);
        sum -= delta;
        y1  -= ((z1 << 4 ^ z1 >> 5) + z1) ^ (sum + *k[sum & 3]);
        y0  -= ((z0 << 4 ^ z0 >> 5) + z0) ^ (sum + *k[sum & 3]);
    }
    *dest[0]=y0; *dest[1]=z0; *dest[2]=y1; *dest[3]=z1;
}

void xtea(unsigned int* key, unsigned int* input, unsigned int *output, char encript) {
    int i;
    unsigned int* d[4];
    const unsigned int* v[4];
    const unsigned int* k[4];

    for(i = 0; i < 4; i++) {
        d[i] = &output[3-i];
        v[i] = &input[3-i];
        k[i] = &key[3-i];
    }

    if (encript)
        xtea_enc(d, v, k);
    else
        xtea_dec(d, v, k);
}

//-----------------------------------------------------------------------------
// Main Function
//-----------------------------------------------------------------------------
int crypt_xtea(int idx) {
    unsigned int key[4], input[4], output[4];

    printf("\n***************     %d      ******************\n\n", idx);

    printf("              -- XTEA %s --\n\n", (tests_c[idx]) ? "ENC" : "DEC");

    // Write the KEY
    key[0] = tests_k[idx][0];
    key[1] = tests_k[idx][1];
    key[2] = tests_k[idx][2];
    key[3] = tests_k[idx][3];

    // Write the plain text to be encripted
    input[0] = tests_n[idx][0];
    input[1] = tests_n[idx][1];
    input[2] = tests_n[idx][2];
    input[3] = tests_n[idx][3];

    printf("input:\t");
    printf("%08X_", input[0]);
    printf("%08X_", input[1]);
    printf("%08X_", input[2]);
    printf("%08X\n", input[3]);

    xtea(key, input, output, tests_c[idx]); // C Application

    // Shows the result
    printf("output:\t");
    printf("%08X_", output[0]);
    printf("%08X_", output[1]);
    printf("%08X_", output[2]);
    printf("%08X\n", output[3]);
    //////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////

    return 0;   

    printf("-- XTEA (DEC) --\n");
    // Write the chiper text to be decripted
    input[0] = 0x089975E9;
    input[1] = 0x2555F334;
    input[2] = 0xCE76E4F2;
    input[3] = 0x4D932AB3;

    printf("input:\t");
    printf("%08X_", input[0]);
    printf("%08X_", input[1]);
    printf("%08X_", input[2]);
    printf("%08X\n", input[3]);

    xtea(key, input, output, DEC); // C Application

    // Shows the result
    printf("output:\t");
    printf("%08X_", output[0]);
    printf("%08X_", output[1]);
    printf("%08X_", output[2]);
    printf("%08X\n", output[3]);

	return 0;
}