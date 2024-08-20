#include <stdio.h>
#include <string.h>

#define SIZE 15

void print_dizi(char dizi[SIZE][SIZE], int uzunluk, int satir, int kolon, int yon) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (yon == 0 && i == satir && j >= kolon && j < kolon + uzunluk) {
                printf("%c ", dizi[i][j]);
            } else if (yon == 1 && j == kolon && i >= satir && i < satir + uzunluk) {
                printf("%c ", dizi[i][j]);
            } else if (yon == 2 && i - satir == j - kolon && i >= satir && i < satir + uzunluk) {
                printf("%c ", dizi[i][j]);
            } else if (yon == 3 && i - satir == kolon - j && i >= satir && i < satir + uzunluk) {
                printf("%c ", dizi[i][j]);
            } else if (yon == 4 && j == kolon && i <= satir && i > satir - uzunluk) {
                printf("%c ", dizi[i][j]);
            } else {
                printf("* ");
            }
        }
        printf("\n");
    }
}

int kelime_bul(char dizi[SIZE][SIZE], char *word) {
    int len = strlen(word);
    int i, j, k;

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j <= SIZE - len; j++) {
            for (k = 0; k < len && dizi[i][j + k] == word[k]; k++);
            if (k == len) {
                print_dizi(dizi, len, i, j, 0);
                return 1;
            }
        }
    }

    for (i = 0; i <= SIZE - len; i++) {
        for (j = 0; j < SIZE; j++) {
            for (k = 0; k < len && dizi[i + k][j] == word[k]; k++);
            if (k == len) {
                print_dizi(dizi, len, i, j, 1);
                return 1;
            }
        }
    }

    for (i = 0; i <= SIZE - len; i++) {
        for (j = 0; j <= SIZE - len; j++) {
            for (k = 0; k < len && dizi[i + k][j + k] == word[k]; k++);
            if (k == len) {
                print_dizi(dizi, len, i, j, 2);
                return 1;
            }
        }
    }

    for (i = 0; i <= SIZE - len; i++) {
        for (j = len - 1; j < SIZE; j++) {
            for (k = 0; k < len && dizi[i + k][j - k] == word[k]; k++);
            if (k == len) {
                print_dizi(dizi, len, i, j, 3);
                return 1;
            }
        }
    }

    for (i = SIZE - 1; i >= len - 1; i--) {
        for (j = 0; j < SIZE; j++) {
            for (k = 0; k < len && dizi[i - k][j] == word[k]; k++);
            if (k == len) {
                print_dizi(dizi, len, i, j, 4);
                return 1;
            }
        }
    }

    return 0;
}

int main() {
    char dizi[SIZE][SIZE];
    char word[SIZE];
    int i, j;

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            scanf(" %c", &dizi[i][j]);
        }
    }

    scanf("%s", word);
    if (!kelime_bul(dizi, word)) {
        for (i = 0; i < SIZE; i++) {
            for (j = 0; j < SIZE; j++) {
                printf("* ");
            }
            printf("\n");
        }
    }

    return 0;
}