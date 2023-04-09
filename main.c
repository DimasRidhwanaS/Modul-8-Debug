#include <stdio.h>
#define MAX_SIZE 7

int visited[MAX_SIZE][MAX_SIZE] = {0};

void dfs(int mat[MAX_SIZE][MAX_SIZE], int i, int j, int patokan, int toleransi) {
    if (i < 0 || j < 0 || i >= MAX_SIZE || j >= MAX_SIZE) {
        return;
    }
    if (visited[i][j] || mat[i][j] < patokan - toleransi || mat[i][j] > patokan + toleransi) {
        return;
    }
    visited[i][j] = 1;
    dfs(mat, i+1, j, patokan, toleransi);
    dfs(mat, i-1, j, patokan, toleransi);
    dfs(mat, i, j+1, patokan, toleransi);
    dfs(mat, i, j-1, patokan, toleransi);
}

int count_clusters(int mat[MAX_SIZE][MAX_SIZE], int patokan, int toleransi) {
    int i, j, count = 0;
    for (i = 0; i < MAX_SIZE; i++) {
        for (j = 0; j < MAX_SIZE; j++) {
            if (!visited[i][j] && mat[i][j] >= patokan - toleransi && mat[i][j] <= patokan + toleransi) {
                dfs(mat, i, j, patokan, toleransi);
                count++;
            }
        }
    }
    return count;
}

int main() {
    char filename[20];
    int patokan, toleransi;
    printf("Masukkan nama file: ");
    scanf("%s", filename);
    printf("Masukkan nilai patokan: ");
    scanf("%d", &patokan);
    printf("Masukkan nilai toleransi: ");
    scanf("%d", &toleransi);

    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("File tidak ditemukan.\n");
        return 0;
    }
    int mat[MAX_SIZE][MAX_SIZE];
    int i, j;
    for (i = 0; i < MAX_SIZE; i++) {
        for (j = 0; j < MAX_SIZE; j++) {
            fscanf(fp, "%d,", &mat[i][j]);
        }
    }
    fclose(fp);

    int jumlah_klaster = count_clusters(mat, patokan, toleransi);
    printf("Jumlah klaster: %d\n", jumlah_klaster);
    return 0;
}
