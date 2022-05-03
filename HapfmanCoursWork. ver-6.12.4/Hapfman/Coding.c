#pragma once
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <malloc.h>

#define MAXWORD 512
int cnt_str[MAXWORD]; //���-�� ��������� ������� � ������
char str[MAXWORD]; //��� ������
int cnt; // ���-�� ��������
typedef char** h_code; // ������ ������� ��������


struct tnode { //��������� ��� ����������� ���-�� �������� � ������.      
    char word;
    int count;
    struct tnode* left;
    struct tnode* right;
};

// ������� ���������� ����
struct tnode* addtree(struct tnode* p, char w) {
    int cond;

    if (p == NULL) {
        p = (struct tnode*)malloc(sizeof(struct tnode));
        p->word = w;
        p->count = 1;
        p->left = p->right = NULL;
    }
    else if ((cond = (w - p->word)) == 0) {

        p->count++;
    }
    else if (cond < 0) {

        p->left = addtree(p->left, w);
    }
    else {

        p->right = addtree(p->right, w);
    }
    return p;
}

// ������� ���������� ���������� ����������
void treereturn(struct tnode* p) {
    if (p != NULL) {
        treereturn(p->right);
        cnt_str[cnt] = p->count;
        str[cnt] = p->word;
        cnt++;
        treereturn(p->left);
    }
}



typedef struct {
    unsigned int weight;
    unsigned int parent;
    unsigned int left;
    unsigned int right;
}node, * h_tree;    // ������������ ���������� ������� ��� �������� ������ ��������

void add_Tree(h_tree h_t, int i, int* s1, int* s2) {
    //�������� ���� ������ ��������, �������� ��� �������� ���� ��� 1 ����� ����
    int min1, min2, k, j = 0;
    for (k = 0; k <= i - 1; k++) {
        if (h_t[k].parent == 0) {
            if (j == 0) {
                min1 = h_t[k].weight;
                *s1 = k;
            }
            else if (j == 1) {
                if (h_t[k].weight < min1) {
                    min2 = min1;
                    *s2 = *s1;
                    min1 = h_t[k].weight;
                    *s1 = k;
                }
                else {
                    min2 = h_t[k].weight;
                    *s2 = k;
                }
            }
            else {
                if (h_t[k].weight < min1) {
                    min2 = min1;
                    *s2 = *s1;
                    min1 = h_t[k].weight;
                    *s1 = k;
                }
                else if (h_t[k].weight >= min1 && h_t[k].weight < min2) {
                    min2 = h_t[k].weight;
                    *s2 = k;
                }
            }
            ++j;
        }
    }
}

void HuffmanCoding(h_tree* h_t, h_code* h_c, int* w, int n) {
    if (n <= 1) return;

    int m = 2 * n - 1; //���� ������
    *h_t = (h_tree)malloc(m * sizeof(node));
    h_tree p = *h_t;

    for (int i = 0; i < n; i++) {
        // ���������� ��� ���� cnt_str, ���������� � *w � p, �������� ����� ����
        p->weight = *w;
        p->parent = 0;
        p->left = -1;
        p->right = -1;
        w++;
        p++;
    }

    for (int i = n; i < m; i++) {
        //���������� ���� ��������� ������ 
        p->weight = 0;
        p->parent = 0;
        p->left = 0;
        p->right = 0;
        p++;
    }

    for (int i = n; i < m; ++i) {
        // ������ ������ �������� 
        // ����� 2 ���� � ��������� ��� 1
        unsigned int s1, s2;
        add_Tree(*h_t, i, &s1, &s2);
        (*h_t)[s1].parent = i;
        (*h_t)[s2].parent = i;
        (*h_t)[i].left = s1;
        (*h_t)[i].right = s2;
        (*h_t)[i].weight = (*h_t)[s1].weight + (*h_t)[s2].weight;//���� - �������� � 2 ���� ����� ����� �� �����
    }


    (*h_c) = (h_code)malloc(n * sizeof(char*));// �������� ������ ��� ��� ��� �������� � �������� �������
    char* cd = (char*)malloc(n * sizeof(char));
    cd[n - 1] = '\0';
    int start, f, c;
    for (int i = 0; i < n; ++i) {
        start = n - 1;
        for (c = i, f = (*h_t)[i].parent; f != 0; c = f, f = (*h_t)[f].parent) {
            if ((*h_t)[f].left == c)
                cd[--start] = '0';
            else cd[--start] = '1';
        }
        (*h_c)[i] = (char*)malloc((n - start) * sizeof(char));
        strcpy((*h_c)[i], &cd[start]);
    }
    free(cd);
}




// � ����� ������������ ������� ����������, ��� ���������� �������� ���������, 
// ��� ��� ���� ���� ����� �������������, �� �������� �������� ����� ������� ��������� 
void sort(int f, int l) { //������� ����������
    int  i, j;
    int L;
    i = f;
    j = l;
    L = cnt_str[(f + l) / 2];
    while (i <= j)
    {
        while ((cnt_str[i] < L) && (i < l))
        {
            i++;
        }
        while ((L < cnt_str[j]) && (j > f))
        {
            j--;
        }
        if (i <= j)
        {
            int b = cnt_str[j];
            cnt_str[j] = cnt_str[i];
            cnt_str[i] = b;
            char b1 = str[j];
            str[j] = str[i];
            str[i] = b1;
            i++;
            j--;
        }
    }
    if (f < j)
    {
        sort(f, j);
    }
    if (i < l)
    {
        sort(i, l);
    }

}


unsigned char ToBits(const char data[], int n)//������� ������� ���������� ������������������ 0 � 1 � ���� � ���� ��� �������
{
    unsigned char byte = 0;
    const char* end = data + n;

    for (; *data && (data < end); ++data)
    {
        byte <<= 1;

        byte |= (*data == '1') ? 1 : 0;
    }

    return byte;
}


void Codding() {
    struct tnode* root;
    char word[MAXWORD];
    root = NULL;
    FILE* fp, * fw;
    fp = fopen("dz2.txt", "r");
    while (fscanf(fp, "%s", &word) != EOF) { //���������� ���-�� �������� � ������.
        for (int i = 0; i < strlen(word); i++) {
            root = addtree(root, word[i]);
        }
        root = addtree(root, ' ');
    }
    cnt = 0;
    treereturn(root);
    fclose(fp);
    int n = cnt;
    sort(0, cnt - 1);

    for (int i = 0; i < n; i++) {
        printf("%d %c\n", cnt_str[i], str[i]);

    }
    printf("%s\n", "");


    h_tree h_t;
    h_code h_c;
    HuffmanCoding(&h_t, &h_c, cnt_str, n);

    FILE* output;
    FILE* fw1 = fopen("Table_Huffman.txt", "w"); // ��� ������ �������

    output = fopen("output1.bin", "wb"); //���� ���� ������������ �������������� ���
    fp = fopen("dz2.txt", "r"); //�������� ����, ������� ����� ����������
    fprintf(fw1, "%d\n", n);


    for (int i = 0; i < n; i++) {
        printf("%c %s\n", str[i], h_c[i]);
        if (str[i] == 32) {
            fprintf(fw1, "%c %s\n", '\\', h_c[i]);
        }
        else {
            fprintf(fw1, "%c %s\n", str[i], h_c[i]);
        }

    }

    fclose(fw1);


    // ������ � ����, ���������� 8 ��� = 1 ����� � char ������, ���� ���� �� ������ 8 ����������� ch1 �������, ����� ��������
    //����� ��� ����� �����, � �� �� ������������ ch1, �� �������� ��� �������� � ����������� 0 � ��������� �����
    int flag = 1;
    int flag1 = 1;
    unsigned char ch1[65535] = "";
    while (flag1 == 1) {
        if (fscanf(fp, "%s", &word) != EOF) {
            if (flag == 1) {
                memset(ch1, 0, sizeof(ch1));
            }
            for (int i = 0; i < strlen(word); i++) {
                for (int j = 0; j < n; ++j) {
                    if (word[i] == str[j]) {
                        strcat(ch1, h_c[j]);
                        break;
                    }
                }
            }
            for (int j = 0; j < n; ++j) {//���� ���� ����� ��������������, ��� ������ ����� ���� �������.
                if (32 == str[j]) {
                    strcat(ch1, h_c[j]);
                    break;
                }
            }
            if (strlen(ch1) % 8 == 0) {
                const char* array1 = ch1;
                if (strlen(ch1) == 8) {
                    unsigned char byte = ToBits(array1, strlen(ch1));
                    fwrite(&byte, 1, 1, output);

                }
                else {
                    int g = strlen(ch1);
                    while (g > 0) {
                        if (g - 8 >= 0) {
                            g -= 8;
                            unsigned char byte = ToBits(array1, 8);
                            fwrite(&byte, 1, 1, output);
                            array1 += 8;
                        }
                        else {
                            int k = 8;
                            while (g - k != 0) {
                                k--;
                            }
                            unsigned char byte = ToBits(array1, k);
                            fwrite(&byte, 1, 1, output);
                            g = 0;
                        }


                    }


                }
                flag = 1;
                array1 = "0";
                unsigned char byte = ToBits(array1, 1);
                fwrite(&byte, 1, 1, output);
            }
            else {
                flag = 0;
            }
        }
        else {
            const char* array1 = ch1;
            if (strlen(ch1) == 8) {
                unsigned char byte = ToBits(array1, strlen(ch1));
                fwrite(&byte, 1, 1, output);

            }
            else {
                int g = strlen(ch1);
                while (g > 0) { //12
                    if (g - 8 >= 0) {
                        g -= 8;
                        unsigned char byte = ToBits(array1, 8);
                        fwrite(&byte, 1, 1, output);
                        array1 += 8;
                    }
                    else {
                        int k = 8;
                        while (g - k != 0) {
                            k--;
                        }
                        unsigned char byte = ToBits(array1, k);
                        fwrite(&byte, 1, 1, output);
                        g = 0;
                    }
                }
            }
            flag1 = 0;
            array1 = "0";
            unsigned char byte = ToBits(array1, 1);
            fwrite(&byte, 1, 1, output);
        }
    }
    memset(ch1, 0, sizeof(ch1));
    fclose(fp);
    fclose(output);
}