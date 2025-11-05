#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef strcasestr
char* strcasestr(const char* tumpukan, const char* penyemat) {
    char* t = (char*)tumpukan;
    char* p = (char*)penyemat;

    if (!*p) return t;

    while (*t) {
        char* t_temp = t;
        char* p_temp = p;

        while (*t_temp && *p_temp &&
               ((*t_temp >= 'A' && *t_temp <= 'Z') ? *t_temp + 32 : *t_temp) ==
               ((*p_temp >= 'A' && *p_temp <= 'Z') ? *p_temp + 32 : *p_temp)) {
            t_temp++;
            p_temp++;
        }

        if (!*p_temp) return t;
        t++;
    }
    return NULL;
}
#endif

typedef struct Lagu {
    int no;
    char Judul[70];
    char Artis[30];
    float Durasi;
    char Genre[20];
    struct Lagu *next;
} Lagu;

Lagu *head = NULL;
int nextId = 1;

void loadData();
void saveData();
int login();
void tambahLagu();
void tampilLagu();
Lagu* cariLaguById(int id);
void updateLagu();
void deleteLagu();
void cariLagu();
void urutanLagu(int mode);
void swapLagu(Lagu *a, Lagu *b);
void bersihkanLayar();
void pause();
void freeMemory();

int main() {
    if (!login()) return 0;
    loadData();
    int pilihan;
    do {
        bersihkanLayar();
        printf("===== Daftar Lagu =====\n");
        printf("1. Tambah Judul Lagu\n");
        printf("2. Tampilkan Lagu\n");
        printf("3. Update Lagu\n");
        printf("4. Hapus Lagu\n");
        printf("5. Cari Lagu\n");
        printf("6. Urutan Lagu\n");
        printf("7. Simpan & Keluar\n");
        printf("=======================\n");
        printf("Pilihan: ");

        if (scanf("%d", &pilihan) != 1) {
            printf("Input tidak valid! Masukkan angka 1-7.\n");
            while (getchar() != '\n');
            pilihan = 0;
            pause();
            continue;
        }

        switch(pilihan) {
            case 1: tambahLagu(); break;
            case 2: tampilLagu(); break;
            case 3: updateLagu(); break;
            case 4: deleteLagu(); break;
            case 5: cariLagu(); break;
            case 6: {
                int m;
                printf("Mode sort: 1=Artis+Durasi, 2=Durasi+Genre (alfabet): ");
                if (scanf("%d", &m) == 1 && (m == 1 || m == 2)) {
                    urutanLagu(m);
                    tampilLagu();
                } else {
                    printf("Mode tidak valid! Pilih 1 atau 2.\n");
                    while (getchar() != '\n');
                    pause();
                }
                break;
            }
            case 7:
                saveData();
                printf("Selesai, data disimpan!\n");
                break;
            default:
                printf("Pilihan salah, pilih 1-7.\n");
                pause();
        }
    } while(pilihan != 7);

    freeMemory();
    return 0;
}

void bersihkanLayar() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pause() {
    printf("Press Enter...");
    while (getchar() != '\n');
    getchar();
}

void bersihkanBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int login() {
    char nama[20], sandi[20];
    const char N[] = "imam", S[] = "sybau";

    while (1) {
        printf("Login: ");
        if (scanf("%19s", nama) != 1) {
            clearerr(stdin);
            bersihkanBuffer();
            continue;
        }
        bersihkanBuffer();

        printf("Password: ");
        if (scanf("%19s", sandi) != 1) {
            clearerr(stdin);
            bersihkanBuffer();
            continue;
        }
        bersihkanBuffer();

        if (strcmp(nama, N) == 0 && strcmp(sandi, S) == 0) {
            printf("Login berhasil!\n");
            return 1;
        } else {
            int nama_ok = strcmp(nama, N) == 0;
            int sandi_ok = strcmp(sandi, S) == 0;

            if (!nama_ok && !sandi_ok)
                printf("Username dan password salah.\n");
            else if (!nama_ok)
                printf("Username salah.\n");
            else
                printf("Password salah.\n");

        }
    }
    return 0;
}


void loadData() {
    FILE *fp = fopen("data.txt", "r");
    if (!fp) {
        printf("File data.txt tidak ditemukan. Memulai dengan data kosong.\n");
        return;
    }

    char line[200];
    while (fgets(line, sizeof(line), fp)) {
        Lagu *b = malloc(sizeof(Lagu));
        if (!b) {
            printf("Error: Tidak dapat mengalokasi memori!\n");
            break;
        }

        if (sscanf(line, "%d|%69[^|]|%29[^|]|%f|%19[^\n]",
                   &b->no, b->Judul, b->Artis, &b->Durasi, b->Genre) == 5) {
            b->next = head;
            head = b;
            if (b->no >= nextId) nextId = b->no + 1;
        } else {
            free(b);
        }
    }
    fclose(fp);
    printf("Data berhasil dimuat.\n");
}

void saveData() {
    FILE *fp = fopen("data.txt", "w");
    if (!fp) {
        printf("Error: Tidak dapat menyimpan data!\n");
        return;
    }

    Lagu *cur = head;
    while (cur) {
        fprintf(fp, "%d|%s|%s|%.2f|%s\n",
                cur->no, cur->Judul, cur->Artis, cur->Durasi, cur->Genre);
        cur = cur->next;
    }
    fclose(fp);
}

void tambahLagu() {
    Lagu *b = malloc(sizeof(Lagu));
    if (!b) {
        printf("Error: Tidak dapat mengalokasi memori!\n");
        return;
    }

    b->no = nextId++;

    while (getchar() != '\n');

    printf("Judul Lagu: ");
    if (!fgets(b->Judul, sizeof(b->Judul), stdin)) {
        free(b);
        return;
    }
    b->Judul[strcspn(b->Judul, "\n")] = 0;

    printf("Artis: ");
    if (!fgets(b->Artis, sizeof(b->Artis), stdin)) {
        free(b);
        return;
    }
    b->Artis[strcspn(b->Artis, "\n")] = 0;

    do {
        printf("Durasi (menit): ");
        if (scanf("%f", &b->Durasi) != 1) {
            printf("Input tidak valid! Masukkan angka.\n");
            while (getchar() != '\n');
            continue;
        }
        if (b->Durasi <= 0) {
            printf("Durasi harus lebih dari 0!\n");
        }
    } while (b->Durasi <= 0);

    while (getchar() != '\n');

    printf("Genre: ");
    if (!fgets(b->Genre, sizeof(b->Genre), stdin)) {
        free(b);
        return;
    }
    b->Genre[strcspn(b->Genre, "\n")] = 0;

    b->next = head;
    head = b;

    printf("Lagu berhasil ditambahkan dengan ID: %d\n", b->no);
    pause();
}

void tampilLagu() {
    if (!head) {
        printf("Tidak ada lagu dalam database.\n");
        pause();
        return;
    }

    int swapped;
    Lagu *ptr1;
    Lagu *lptr = NULL;

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->no > ptr1->next->no) {
                int tempId = ptr1->no;
                float tempDurasi = ptr1->Durasi;
                char tempJudul[100], tempArtis[100], tempGenre[100];

                strcpy(tempJudul, ptr1->Judul);
                strcpy(tempArtis, ptr1->Artis);
                strcpy(tempGenre, ptr1->Genre);

                ptr1->no = ptr1->next->no;
                ptr1->Durasi = ptr1->next->Durasi;
                strcpy(ptr1->Judul, ptr1->next->Judul);
                strcpy(ptr1->Artis, ptr1->next->Artis);
                strcpy(ptr1->Genre, ptr1->next->Genre);

                ptr1->next->no = tempId;
                ptr1->next->Durasi = tempDurasi;
                strcpy(ptr1->next->Judul, tempJudul);
                strcpy(ptr1->next->Artis, tempArtis);
                strcpy(ptr1->next->Genre, tempGenre);

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);

    bersihkanLayar();
    printf("\n+----+------------------------------+----------------------+--------+------------------+\n");
    printf("| No | Judul                        | Artis                | Durasi | Genre            |\n");
    printf("+----+------------------------------+----------------------+--------+------------------+\n");

    Lagu *cur = head;
    while (cur) {
        printf("| %2d | %-28.28s | %-20.20s | %6.2f | %-16.16s |\n",
               cur->no, cur->Judul, cur->Artis, cur->Durasi, cur->Genre);
        cur = cur->next;
    }
    printf("+----+------------------------------+----------------------+--------+------------------+\n");
    pause();
}


Lagu* cariLaguById(int id) {
    Lagu *cur = head;
    while (cur && cur->no != id) {
        cur = cur->next;
    }
    return cur;
}

void updateLagu() {
    int no;
    printf("Nomor lagu yang akan diupdate: ");
    if (scanf("%d", &no) != 1) {
        printf("Input tidak valid!\n");
        while (getchar() != '\n');
        pause();
        return;
    }

    Lagu *b = cariLaguById(no);
    if (!b) {
        printf("Lagu dengan ID %d tidak ditemukan.\n", no);
        pause();
        return;
    }

    printf("Data saat ini:\n");
    printf("Judul: %s\n", b->Judul);
    printf("Artis: %s\n", b->Artis);
    printf("Durasi: %.2f menit\n", b->Durasi);
    printf("Genre: %s\n", b->Genre);
    printf("\nMasukkan data baru:\n");

    while (getchar() != '\n');

    printf("Judul baru [%s]: ", b->Judul);
    if (fgets(b->Judul, sizeof(b->Judul), stdin)) {
        b->Judul[strcspn(b->Judul, "\n")] = 0;
    }

    printf("Artis baru [%s]: ", b->Artis);
    if (fgets(b->Artis, sizeof(b->Artis), stdin)) {
        b->Artis[strcspn(b->Artis, "\n")] = 0;
    }

    do {
        printf("Durasi baru [%.2f]: ", b->Durasi);
        if (scanf("%f", &b->Durasi) != 1) {
            printf("Input tidak valid! Masukkan angka.\n");
            while (getchar() != '\n');
            continue;
        }
        if (b->Durasi <= 0) {
            printf("Durasi harus lebih dari 0!\n");
        }
    } while (b->Durasi <= 0);

    while (getchar() != '\n');

    printf("Genre baru [%s]: ", b->Genre);
    if (fgets(b->Genre, sizeof(b->Genre), stdin)) {
        b->Genre[strcspn(b->Genre, "\n")] = 0;
    }

    printf("Lagu berhasil diupdate!\n");
    pause();
}

void deleteLagu() {
    int id;
    printf("ID lagu yang akan dihapus: ");
    if (scanf("%d", &id) != 1) {
        printf("Input tidak valid!\n");
        while (getchar() != '\n');
        pause();
        return;
    }

    Lagu *cur = head, *prev = NULL;
    while (cur && cur->no != id) {
        prev = cur;
        cur = cur->next;
    }

    if (!cur) {
        printf("Lagu dengan ID %d tidak ditemukan.\n", id);
        pause();
        return;
    }

    printf("Menghapus lagu: %s - %s\n", cur->Judul, cur->Artis);

    if (prev) {
        prev->next = cur->next;
    } else {
        head = cur->next;
    }

    free(cur);
    printf("Lagu berhasil dihapus!\n");
    pause();
}

void cariLagu() {
    char key[70];
    while (getchar() != '\n');

    printf("Masukkan kata kunci (judul/artis): ");
    if (!fgets(key, sizeof(key), stdin)) {
        return;
    }
    key[strcspn(key, "\n")] = 0;

    if (strlen(key) == 0) {
        printf("Kata kunci tidak boleh kosong!\n");
        pause();
        return;
    }

    int found = 0;
    Lagu *cur = head;

    printf("\nHasil pencarian untuk '%s':\n", key);
    printf("+----+------------------------------+----------------------+--------+------------------+\n");
    printf("| ID | Judul                        | Artis                | Durasi | Genre            |\n");
    printf("+----+------------------------------+----------------------+--------+------------------+\n");

    while (cur) {
        if (strcasestr(cur->Judul, key) || strcasestr(cur->Artis, key)) {
            printf("| %2d | %-28.28s | %-20.20s | %6.2f | %-16.16s |\n",
                   cur->no, cur->Judul, cur->Artis, cur->Durasi, cur->Genre);
            found++;
        }
        cur = cur->next;
    }

    if (!found) {
        printf("Tidak ada lagu yang cocok dengan '%s'.\n", key);
    } else {
        printf("+----+------------------------------+----------------------+--------+------------------+\n");
        printf("Ditemukan %d lagu.\n", found);
    }
    pause();
}

void urutanLagu(int mode) {
    if (!head || !head->next) return;

    int swapped;
    Lagu *ptr, *lptr = NULL;

    do {
        swapped = 0;
        ptr = head;

        while (ptr->next != lptr) {
            int shouldSwap = 0;

            if (mode == 1) {
                int cmp = strcmp(ptr->Artis, ptr->next->Artis);
                if (cmp > 0 || (cmp == 0 && ptr->Durasi > ptr->next->Durasi)) {
                    shouldSwap = 1;
                }
            } else if (mode == 2) {
                if (ptr->Durasi > ptr->next->Durasi ||
                    (ptr->Durasi == ptr->next->Durasi &&
                     strcmp(ptr->Genre, ptr->next->Genre) > 0)) {
                    shouldSwap = 1;
                }
            }

            if (shouldSwap) {
                swapLagu(ptr, ptr->next);
                swapped = 1;
            }
            ptr = ptr->next;
        }
        lptr = ptr;
    } while (swapped);

    printf("Data berhasil diurutkan!\n");
}

void swapLagu(Lagu *a, Lagu *b) {
    int tempId = a->no;
    char tempJudul[70], tempArtis[30], tempGenre[20];
    float tempDurasi = a->Durasi;

    strcpy(tempJudul, a->Judul);
    strcpy(tempArtis, a->Artis);
    strcpy(tempGenre, a->Genre);

    a->no = b->no;
    strcpy(a->Judul, b->Judul);
    strcpy(a->Artis, b->Artis);
    strcpy(a->Genre, b->Genre);
    a->Durasi = b->Durasi;

    b->no = tempId;
    strcpy(b->Judul, tempJudul);
    strcpy(b->Artis, tempArtis);
    strcpy(b->Genre, tempGenre);
    b->Durasi = tempDurasi;
}

void freeMemory() {
    Lagu *cur = head;
    while (cur) {
        Lagu *temp = cur;
        cur = cur->next;
        free(temp);
    }
    head = NULL;
}
