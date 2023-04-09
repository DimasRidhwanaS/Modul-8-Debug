#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10

int map[MAX_N][MAX_N];
int visited[MAX_N][MAX_N];

int n;

int count_clusters(int x, int y, int lower_bound, int upper_bound) {
    if (x < 0 || x >= n || y < 0 || y >= n) {
        return 0;
    }

    if (visited[x][y]) {
        return 0;
    }

    if (map[x][y] < lower_bound || map[x][y] > upper_bound) {
        return 0;
    }

    visited[x][y] = 1;

    int count = 1;

    count += count_clusters(x - 1, y, lower_bound, upper_bound);
    count += count_clusters(x + 1, y, lower_bound, upper_bound);
    count += count_clusters(x, y - 1, lower_bound, upper_bound);
    count += count_clusters(x, y + 1, lower_bound, upper_bound);

    return count;
}

int main() {
    char filename[100];

    printf("Masukkan nama file: ");
    scanf("%s", filename);

    printf("Masukkan nilai patokan: ");
    int patokan;
    scanf("%d", &patokan);

    printf("Masukkan nilai toleransi: ");
    int toleransi;
    scanf("%d", &toleransi);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("File tidak dapat dibuka.\n");
        return 1;
    }

    fscanf(file, "%d", &n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(file, "%d", &map[i][j]);
        }
    }

    fclose(file);

    int lower_bound = patokan - toleransi;
    int upper_bound = patokan + toleransi;

    int num_clusters = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (visited[i][j]) {
                continue;
            }

            if (map[i][j] < lower_bound || map[i][j] > upper_bound) {
                continue;
            }

            num_clusters += (count_clusters(i, j, lower_bound, upper_bound) > 1);
        }
    }

    printf("Jumlah klaster: %d\n", num_clusters);

    return 0;
}
