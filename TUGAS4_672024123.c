#include <stdio.h>
#include <string.h>

int countOccurrences(const char *teks, const char *pola) {
    int count = 0;
    int lenPola = strlen(pola);
    int lenTeks = strlen(teks);

    for (int i = 0; i <= lenTeks - lenPola; i++) {
        if (strncmp(&teks[i], pola, lenPola) == 0) {
            count++;
        }
    }
    return count;
}

int main() {
    char target[101];
    int jumlah, panjang;
    char kelompok_angka[100][101];
    char gabungan[10001] = "";
    scanf("%s", target);

    scanf("%d %d", &jumlah, &panjang);
    for (int i = 0; i < jumlah; i++) {
        scanf("%s", kelompok_angka[i]);
        strcat(gabungan, kelompok_angka[i]);
    }

    int hasil = countOccurrences(gabungan, target);
    printf("%d\n", hasil);

    return 0;
}
