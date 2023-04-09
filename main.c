#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10

int visited[MAX_N][MAX_N] = {{0}};
int matrix[MAX_N][MAX_N];
int cluster_count = 0;

void DFS(int row, int col, int threshold_low, int threshold_high, int N) {
    if (visited[row][col]) return;
    visited[row][col] = 1;

    // Jika nilai di dalam cluster, maka DFS ke atas, bawah, kiri dan kanan
    if (matrix[row][col] >= threshold_low && matrix[row][col] <= threshold_high) {
        if (row > 0) DFS(row - 1, col, threshold_low, threshold_high, N);
        if (row < N - 1) DFS(row + 1, col, threshold_low, threshold_high, N);
        if (col > 0) DFS(row, col - 1, threshold_low, threshold_high, N);
        if (col < N - 1) DFS(row, col + 1, threshold_low, threshold_high, N);
    }
}

int main() {
    char filename[50];
    int threshold_low, threshold_high, N;

    printf("Masukkan nama file: ");
    scanf("%s", filename);

    FILE* fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("File tidak dapat dibuka atau tidak ada.\n");
        exit(EXIT_FAILURE);
    }

    fscanf(fp, "%d", &N);

    // Membaca matriks dari file
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fscanf(fp, "%d", &matrix[i][j]);
        }
    }

    fclose(fp);

    printf("Masukkan nilai patokan: ");
    scanf("%d", &threshold_low);

    printf("Masukkan nilai toleransi: ");
    scanf("%d", &threshold_high);

    threshold_high += threshold_low;

    // Menghitung jumlah cluster
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (!visited[i][j] && matrix[i][j] >= threshold_low && matrix[i][j] <= threshold_high) {
                DFS(i, j, threshold_low, threshold_high, N);
                cluster_count++;
            }
        }
    }

    printf("Jumlah klaster: %d\n", cluster_count);

    return 0;
}
