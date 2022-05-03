#pragma once
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <malloc.h>

//глоб. пременные
#define MAXWORD 512
char symbols[MAXWORD]; //символы для декодирования
char t_code[MAXWORD][MAXWORD]; //таблица кодов Хаффмана



char* OutByte(unsigned char byte, char bits[])//из чар символа в последовательность 0 и 1
{
    size_t i;
    for (i = 0; i < 8; i++)
    {
        bits[7 - i] = (byte & 1) ? '1' : '0';
        byte >>= 1;
    }

    return bits;
}

int decoding() {
    int n1 = 0;
    FILE* tb;
    tb = fopen("Table_Huffman.txt", "r");
    char word[MAXWORD];
   
    fscanf(tb, "%s", &word);
    char* cnti = word;
    int k1 = 0;

    int fl = 1;
    while (fl == 1) {

        if (fscanf(tb, "%s", &word) != EOF) {
            symbols[k1] = word[0];
            fscanf(tb, "%s", &word);
            strcpy(t_code[k1], word);
            k1++;
        }
        else { fl = 0; }

    }
    fclose(tb);
    n1 = k1;
    return n1;
}


void DeCodding() {
    int n1 = decoding();
    FILE* f = fopen("output1.bin", "rb");
    FILE* fw = fopen("output3.txt", "w");
    unsigned char byte;
    unsigned char out[65535] = "";

    int flag2 = 1;
    while (fread(&byte, 1, 1, f) == 1)
    {
        char bits[9] = { 0 };
        if (byte == 0) {
            unsigned char out2[MAXWORD] = "";
            for (int i = 0; i < strlen(out); i++) {

                if (out[i] == '0') {
                    strcat(out2, "0");
                }
                else { strcat(out2, "1"); }
                for (int j = 0; j < n1; ++j) {
                    if (!strcmp(out2, t_code[j])) {
                        if (symbols[j] == 92)
                            fprintf(fw, "%s", " ");
                        else
                            fprintf(fw, "%c", symbols[j]);
                        memset(out2, 0, sizeof(out2));
                        break;
                    }
                }
            }
            memset(out, 0, sizeof(out));
        }
        else {
            strcat(out, OutByte(byte, bits));
        }
    }
    fclose(f);
    fclose(fw);


}