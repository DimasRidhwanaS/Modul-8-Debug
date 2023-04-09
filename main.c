/** EL2208 Praktikum Pemecahan Masalah dengan C 2022/2023
 *   Modul               : 8 - Advanced Algorithms
 *   Hari dan Tanggal    : Rabu, 5 April 2023
 *   Nama (NIM)          : Dimas Ridhwana Shalsareza (13221076)
 *   Nama File           : main.c
 *   Deskripsi           : 
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

int map[MAX_SIZE][MAX_SIZE];
int visited[MAX_SIZE][MAX_SIZE];

void read_map(char *filename, int n) {
    FILE *file = fopen(filename, "r");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            fscanf(file, "%d,", &map[i][j]);
        }
    }
    fclose(file);
}

void dfs(int i, int j, int n, int patokan, int toleransi) {
    if(i < 0 || j < 0 || i >= n || j >= n) return;
    if(visited[i][j]) return;
    if(abs(map[i][j] - patokan) > toleransi) return;
    visited[i][j] = 1;
    dfs(i - 1, j, n, patokan, toleransi);
    dfs(i + 1, j, n, patokan, toleransi);
    dfs(i, j - 1, n, patokan, toleransi);
    dfs(i, j + 1, n, patokan, toleransi);
    dfs(i - 1, j - 1, n, patokan, toleransi);
    dfs(i - 1, j + 1, n, patokan, toleransi);
    dfs(i + 1, j - 1, n, patokan, toleransi);
    dfs(i + 1, j + 1, n, patokan, toleransi);
}

int count_clusters(int n, int patokan, int toleransi) {
    int klaster = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(!visited[i][j] && abs(map[i][j] - patokan) <= toleransi) {
                dfs(i, j, n, map[i][j], toleransi);
                klaster++;
            }
        }
    }
    return klaster;
}

int main() {
    char filename[100];
    int n, patokan, toleransi;
    printf("Masukkan nama file: ");
    scanf("%s", filename);
    printf("Masukkan nilai patokan: ");
    scanf("%d", &patokan);
    printf("Masukkan nilai toleransi: ");
    scanf("%d", &toleransi);
    printf("\n");
    n = MAX_SIZE;
    read_map(filename, n);
    int klaster = count_clusters(n, patokan, toleransi);
    printf("Jumlah klaster: %d\n", klaster);
    return 0;
}
