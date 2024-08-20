#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int n, m;
char dizi[MAX][MAX];
int gez[MAX][MAX];

int dx[] = {-1, 1, 0, 0, -1, -1, 1, 1};
int dy[] = {0, 0, -1, 1, -1, 1, -1, 1};

int is_valid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && m && dizi[x][y] == '*' && !gez[x][y];
}

int dfs(int x, int y) {
    gez[x][y] = 1;
    int count = 1;
    
    for (int i = 0; i < 8; i++) {
        int new_x = x + dx[i];
        int new_y = y + dy[i];
        if (is_valid(new_x, new_y)) {
            count += dfs(new_x, new_y);
        }
    }
    
    return count;
}

int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            dizi[i][j] = '.';
            gez[i][j] = 0;
        }
    }

    while (1) {
        int r, c;
        scanf("%d", &r);
        if (r == -1) break;
        scanf("%d", &c);
        dizi[r][c] = '*';
    }

    int blob_sizes[MAX];
    int blob_count = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (dizi[i][j] == '*' && !gez[i][j]) {
                int size = dfs(i, j);
                blob_sizes[blob_count++] = size;
            }
        }
    }

    qsort(blob_sizes, blob_count, sizeof(int), cmp);

    printf("%d ", blob_count);
    for (int i = 0; i < blob_count; i++) {
        printf("%d ", blob_sizes[i]);
    }

    return 0;
}