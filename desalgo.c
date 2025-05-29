#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Initial Permutation Table
int IP[] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9 , 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

// Final Permutation Table
int FP[] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9 , 49, 17, 57, 25
};

// Expansion Table
int E[] = {
    32, 1 , 2 , 3 , 4 , 5 ,
    4 , 5 , 6 , 7 , 8 , 9 ,
    8 , 9 , 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1
};

// S-boxes
int S_BOX[8][4][16] = {
    // S1
    {
        {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
        {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
        {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
        {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
    },
    // S2
    {
        {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
        {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
        {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
        {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
    },
    // S3
    {
        {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
        {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
        {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
        {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
    },
    // S4
    {
        {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
        {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
        {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
        {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
    },
    // S5
    {
        {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
        {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
        {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
        {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
    },
    // S6
    {
        {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
        {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
        {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
        {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
    },
    // S7
    {
        {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
        {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
        {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
        {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
    },
    // S8
    {
        {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
        {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
        {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
        {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
    }
};

// P permutation table
int P[] = {
    16, 7, 20, 21,
    29, 12, 28, 17,
    1 , 15, 23, 26,
    5 , 18, 31, 10,
    2 , 8 , 24, 14,
    32, 27, 3 , 9 ,
    19, 13, 30, 6 ,
    22, 11, 4 , 25
};

// PC-1
int PC1[] = {
    57,49,41,33,25,17,9,
    1,58,50,42,34,26,18,
    10,2,59,51,43,35,27,
    19,11,3,60,52,44,36,
    63,55,47,39,31,23,15,
    7,62,54,46,38,30,22,
    14,6,61,53,45,37,29,
    21,13,5,28,20,12,4
};

// PC-2
int PC2[] = {
    14,17,11,24,1,5,
    3,28,15,6,21,10,
    23,19,12,4,26,8,
    16,7,27,20,13,2,
    41,52,31,37,47,55,
    30,40,51,45,33,48,
    44,49,39,56,34,53,
    46,42,50,36,29,32
};

// Number of left shifts per round
int SHIFTS[] = {
    1, 1, 2, 2, 2, 2, 2, 2,
    1, 2, 2, 2, 2, 2, 2, 1
};

// Permutation function
void permute(int *input, int *output, int *table, int n) {
    for(int i = 0; i < n; i++)
        output[i] = input[table[i]-1];
}

// Left rotate
void left_shift(int *key_half, int shifts) {
    int temp[28];
    for(int i = 0; i < 28; i++)
        temp[i] = key_half[(i + shifts) % 28];
    memcpy(key_half, temp, sizeof(temp));
}

// XOR function
void xor(int *a, int *b, int *out, int n) {
    for(int i = 0; i < n; i++)
        out[i] = a[i] ^ b[i];
}

// S-box substitution
void sbox_substitution(int *input, int *output) {
    for(int i = 0; i < 8; i++) {
        int row = (input[i*6]<<1) + input[i*6+5];
        int col = (input[i*6+1]<<3) + (input[i*6+2]<<2) + (input[i*6+3]<<1) + input[i*6+4];
        int val = S_BOX[i][row][col];
        for(int j = 0; j < 4; j++)
            output[i*4 + j] = (val >> (3-j)) & 1;
    }
}

// DES f-function
void feistel(int *R, int *K, int *output) {
    int expanded[48], xored[48], sbox_out[32];
    permute(R, expanded, E, 48);
    xor(expanded, K, xored, 48);
    sbox_substitution(xored, sbox_out);
    permute(sbox_out, output, P, 32);
}

// Key schedule generation
void generate_keys(int *key, int keys[16][48]) {
    int permuted_key[56], C[28], D[28];
    permute(key, permuted_key, PC1, 56);
    memcpy(C, permuted_key, 28 * sizeof(int));
    memcpy(D, permuted_key + 28, 28 * sizeof(int));

    for(int i = 0; i < 16; i++) {
        left_shift(C, SHIFTS[i]);
        left_shift(D, SHIFTS[i]);

        int CD[56];
        memcpy(CD, C, 28 * sizeof(int));
        memcpy(CD + 28, D, 28 * sizeof(int));
        permute(CD, keys[i], PC2, 48);
    }
}

// Full DES encryption
void des_encrypt(int *plaintext, int *key, int *ciphertext) {
    int IPtext[64], FPtext[64];
    int L[17][32], R[17][32], temp[32];
    int keys[16][48];

    permute(plaintext, IPtext, IP, 64);

    memcpy(L[0], IPtext, 32 * sizeof(int));
    memcpy(R[0], IPtext + 32, 32 * sizeof(int));

    generate_keys(key, keys);

    for(int i = 1; i <= 16; i++) {
        memcpy(L[i], R[i-1], 32 * sizeof(int));
        feistel(R[i-1], keys[i-1], temp);
        xor(L[i-1], temp, R[i], 32);
    }

    int preoutput[64];
    memcpy(preoutput, R[16], 32 * sizeof(int));
    memcpy(preoutput + 32, L[16], 32 * sizeof(int));

    permute(preoutput, ciphertext, FP, 64);
}

// Convert hex to binary array
void hex_to_bin(char *hex, int *bin) {
    for (int i = 0; i < 16; i++) {
        int val = (hex[i] >= 'A') ? (hex[i] - 'A' + 10) : (hex[i] - '0');
        for (int j = 0; j < 4; j++)
            bin[i*4 + j] = (val >> (3 - j)) & 1;
    }
}

// Convert binary array to hex string
void bin_to_hex(int *bin, char *hex) {
    for (int i = 0; i < 16; i++) {
        int val = 0;
        for (int j = 0; j < 4; j++)
            val = (val << 1) + bin[i*4 + j];
        hex[i] = (val < 10) ? (val + '0') : (val - 10 + 'A');
    }
    hex[16] = '\0';
}
int main() {
    char plain_hex[17] = "0123456789ABCDEF";
    char key_hex[17] =   "133457799BBCDFF1";

    int plaintext[64], key[64], ciphertext[64];
    char cipher_hex[17];

    hex_to_bin(plain_hex, plaintext);
    hex_to_bin(key_hex, key);

    int num_iterations = 100000; // Number of DES encryptions

    clock_t start_time = clock(); // Start measuring time

    for (int i = 0; i < num_iterations; i++) {
        des_encrypt(plaintext, key, ciphertext);
    }

    clock_t end_time = clock(); // End measuring time

    bin_to_hex(ciphertext, cipher_hex);

    double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Plaintext : %s\n", plain_hex);
    printf("Key       : %s\n", key_hex);
    printf("Ciphertext: %s\n", cipher_hex);
    printf("Time taken for %d iterations: %.3f seconds\n", num_iterations, time_taken);

    return 0;
}

