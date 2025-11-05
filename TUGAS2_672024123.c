#include <stdio.h>

int fibonacci(int nilai) {
    if (nilai == 0) return 0;
    if (nilai == 1) return 1;
    return fibonacci(nilai - 1) + fibonacci(nilai - 2);
}

int main() {
    int angka, indeks;

    printf("Masukkan bilangan: ");
    scanf("%d", &angka);

    printf("Deret fibonacci:\n");
    for (indeks = 0; indeks < angka; indeks++) {
        printf("%d ", fibonacci(indeks));
    }

    printf("\nPress any key to continue...\n");
    getchar();
    getchar();
    return 0;
}
