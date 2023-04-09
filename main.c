#include <stdio.h>
#define MAX_N 10

int matrix[MAX_N][MAX_N];
int visited[MAX_N][MAX_N];
int cluster[MAX_N][MAX_N];
int n;

void createCluster(int row, int col, int clusterNo, int patokan, int toleransi) {
    if(row < 0 || col < 0 || row >= n || col >= n) {
        return;
    }
    if(visited[row][col] || matrix[row][col] < patokan-toleransi || matrix[row][col] > patokan+toleransi) {
        return;
    }
    visited[row][col] = 1;
    cluster[row][col] = clusterNo;
    createCluster(row+1, col, clusterNo, patokan, toleransi);
    createCluster(row-1, col, clusterNo, patokan, toleransi);
    createCluster(row, col+1, clusterNo, patokan, toleransi);
    createCluster(row, col-1, clusterNo, patokan, toleransi);
}

int main() {
    char fileName[50];
    int patokan, toleransi, i, j, k, l, clusterCount = 0;

    printf("Masukkan nama file: ");
    scanf("%s", fileName);

    FILE *file = fopen(fileName, "r");
    if(file == NULL) {
        printf("File tidak ditemukan.\n");
        return 0;
    }

    fscanf(file, "%d", &n);
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            fscanf(file, "%d", &matrix[i][j]);
        }
    }
    fclose(file);

    printf("Masukkan nilai patokan: ");
    scanf("%d", &patokan);

    printf("Masukkan nilai toleransi: ");
    scanf("%d", &toleransi);

    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            if(!visited[i][j] && matrix[i][j] >= patokan-toleransi && matrix[i][j] <= patokan+toleransi) {
                clusterCount++;
                createCluster(i, j, clusterCount, patokan, toleransi);
            }
        }
    }

    printf("Jumlah klaster: %d\n", clusterCount);

    return 0;
}
