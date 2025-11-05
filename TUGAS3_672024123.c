#include <stdio.h>

void sorting(int array[], int nilai) {
    int i, j, temp;
    for (i = 0; i < nilai; i++) {
        for (j = 0; j < nilai - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

void inputArray(int array[], int panjang, int arrayKe) {
    printf("Masukkan nilai untuk array %d:\n", arrayKe);
    for (int i = 0; i < panjang; i++) {
        int value;
        do {
            printf("Index [%d]: ", i);
            scanf("%d", &value);
            if (value < 0) {
                printf("Maaf, tidak menerima bilangan negatif.\n");
            }
        } while (value < 0);
        array[i] = value;
    }
    printf("\n");
}

int main() {
    int panjang1, panjang2;

    do {
        printf("Panjang Array 1: ");
        scanf("%d", &panjang1);
        if (panjang1 <= 0) {
            printf("Panjang array harus lebih dari 0!\n");
        }
    } while (panjang1 <= 0);

    do {
        printf("Panjang Array 2: ");
        scanf("%d", &panjang2);
        if (panjang2 <= 0) {
            printf("Panjang array harus lebih dari 0!\n");
        }
    } while (panjang2 <= 0);

    int array1[panjang1], array2[panjang2];

    printf("\n");
    inputArray(array1, panjang1, 1);
    inputArray(array2, panjang2, 2);

    printf("Isi dari Array 1:\n");
    for (int i = 0; i < panjang1; i++) {
        printf("%d\t", array1[i]);
    }
    printf("\n");

    printf("Isi dari Array 2:\n");
    for (int i = 0; i < panjang2; i++) {
        printf("%d\t", array2[i]);
    }
    printf("\n");

    int totalPanjang = panjang1 + panjang2;
    int gabungan[totalPanjang];

    for (int i = 0; i < panjang1; i++) {
        gabungan[i] = array1[i];
    }

    for (int i = 0; i < panjang2; i++) {
        gabungan[panjang1 + i] = array2[i];
    }

    sorting(gabungan, totalPanjang);

    printf("Hasil setelah digabung dan diurutkan:\n");
    for (int i = 0; i < totalPanjang; i++) {
        printf("%d ", gabungan[i]);
    }
    printf("\n");

    return 0;
}
