#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10

int main() {
    int matrix[MAX_N][MAX_N];
    int n, patokan, toleransi;

    // Input nama file
    char namafile[100];
    printf("Masukkan nama file: ");
    scanf("%s", namafile);

    // Baca matrix dari file
    FILE *fp = fopen(namafile, "r");
    if (fp == NULL) {
        printf("File tidak ditemukan.\n");
        return 0;
    }

    fscanf(fp, "%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(fp, "%d,", &matrix[i][j]);
        }
    }
    fclose(fp);

    // Input nilai patokan dan nilai toleransi
    printf("Masukkan nilai patokan: ");
    scanf("%d", &patokan);
    printf("Masukkan nilai toleransi: ");
    scanf("%d", &toleransi);

    // Buat klaster dan hitung jumlah klaster
    int klaster[MAX_N * MAX_N] = {0};
    int num_klaster = 0;
    for (int k = patokan - toleransi; k <= patokan + toleransi; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == k && klaster[i*n+j] == 0) {
                    klaster[i*n+j] = num_klaster + 1;
                    for (int di = -1; di <= 1; di++) {
                        for (int dj = -1; dj <= 1; dj++) {
                            if (i+di >= 0 && i+di < n && j+dj >= 0 && j+dj < n && matrix[i+di][j+dj] >= patokan-toleransi && matrix[i+di][j+dj] <= patokan+toleransi && klaster[(i+di)*n+(j+dj)] == 0) {
                                klaster[(i+di)*n+(j+dj)] = num_klaster + 1;
                            }
                        }
                    }
                    num_klaster++;
                }
            }
        }
    }

    // Output jumlah klaster
    printf("Jumlah klaster: %d\n", num_klaster);

    return 0;
}
