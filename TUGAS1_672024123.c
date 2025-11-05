#include <stdio.h>
int baris, kolom;

void main() {
    printf("Masukkan panjang baris: ");
    scanf("%d", &baris);
    printf("Masukkan panjang kolom: ");
    scanf("%d", &kolom);

    int matrik[baris][kolom];

    printf("Masukkan elemen matrik: \n");
    for (int i=0; i< baris; i++) {
        for(int j=0; j< kolom; j++) {
            printf("Elemen [%d, %d]: ", i+1, j+1);
            scanf("%d", &matrik[i][j]);
        }
    }

    printf("\nIsi Matrik: \n");
    for (int i=0; i< baris; i++) {
        for(int j=0; j< kolom; j++) {
            printf("%d ", matrik[i][j]);
        }
        printf("\n");
    }

    int total = 0;
    for(int i=0; i< baris; i++) {
        for(int j=0; j< kolom; j++){
            total += matrik[i][j];
        }
    }

    float average = (float)total / (baris * kolom);
    printf("\nJumlah semua bilangan dalam matriks adalah: %d\n", total);
    printf("Rata-rata dari matriks adalah: %d/%d = %.2f\n", total, baris * kolom, average);

    printf("\nMatriks dengan angka Genap '0': \n");
    for(int i=0; i< baris; i++) {
        for(int j=0; j< kolom; j++) {
            if (matrik[i][j] % 2 == 0) {
                printf("0 ");
            } else {
                printf("%d ", matrik[i][j]);
            }
        }
        printf("\n");
    }

    printf("\nMatriks dengan angka kelipatan 5 'L': \n");
    for(int i=0; i< baris; i++) {
        for(int j=0; j< kolom; j++) {
            if (matrik[i][j] % 5 == 0) {
                printf("L ");
            } else {
                printf("%d ", matrik[i][j]);
            }
        }
        printf("\n");
    }

    printf("\nMatriks Transpose\n");
    for(int j=0; j< kolom; j++) {
        for(int i=0; i< baris; i++) {
            printf("%d ", matrik[i][j]);
        }
        printf("\n");
    }
}
