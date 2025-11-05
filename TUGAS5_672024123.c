#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct mahasiswa {
    char nama[70];
    char nim[25];
    struct mahasiswa *next;
};

void tambahMahasiswa(struct mahasiswa **head) {
    struct mahasiswa *baru = malloc(sizeof(struct mahasiswa));
    if (!baru) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    printf("Masukkan Nama Mahasiswa: ");
    getchar();
    fgets(baru->nama, sizeof(baru->nama), stdin);
    baru->nama[strcspn(baru->nama, "\n")] = '\0';

    printf("Masukkan NIM Mahasiswa: ");
    scanf("%24s", baru->nim);

    baru->next = NULL;

    if (*head == NULL) {
        *head = baru;
    } else {
        struct mahasiswa *cur = *head;
        while (cur->next)
            cur = cur->next;
        cur->next = baru;
    }
    printf("Data berhasil ditambahkan.\n");
}

void tampilMahasiswa(struct mahasiswa *head) {
    if (!head) {
        printf("Tidak ada data mahasiswa.\n");
        return;
    }

    struct mahasiswa *cur = head;
    int idx = 1;
    printf("\n=== Daftar Mahasiswa UKSW ===\n");
    while (cur) {
        printf("%d. Nama: %s | NIM: %s\n", idx++, cur->nama, cur->nim);
        cur = cur->next;
    }
    printf("=============================\n");
}

void bersihkanList(struct mahasiswa **head) {
    struct mahasiswa *cur = *head;
    while (cur) {
        struct mahasiswa *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    *head = NULL;
}

int main() {
    struct mahasiswa *head = NULL;
    int pilihan;

    do {
        printf("\nMenu:\n");
        printf("1. Masukkan Nama Mahasiswa dan NIM\n");
        printf("2. Tampilkan Semua\n");
        printf("0. Keluar\n");
        printf("Pilih: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                tambahMahasiswa(&head);
                break;
            case 2:
                tampilMahasiswa(head);
                break;
            case 0:
                printf("Terima kasih sudah menggunakan program ini.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 0);

    bersihkanList(&head);
    return 0;
}
