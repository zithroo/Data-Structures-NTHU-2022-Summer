#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FLASE 0
#define MAX_V 1001

void clear(_Bool (* graph) [MAX_V], int vertex) {
    for(int i = 1; i <= vertex; i++) {
        for(int j = 1; j <= vertex; j++)
            graph[i][j] = FLASE;
    }
}

void print_matrix(_Bool (* A)[MAX_V], int n) {
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++)
            printf("%d ", A[i][j]);
        printf("\n");
    }
}

int main() {
    int t, n, m, q; // times, vertices, edges, queries
    _Bool g1[MAX_V][MAX_V];
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d%d", &n, &m, &q);
        clear(g1, n);
        int v1, v2;
        while(m--) {
            scanf("%d%d", &v1, &v2);
            g1[v1][v2] = TRUE;
            g1[v2][v1] = TRUE;
        }
        // print_matrix(g1, n);
        while(q--) {
            scanf("%d%d", &v1, &v2);
            _Bool flag = FLASE;

            for(int i = 1; i <= n; i++) {
                if(i == v2 || i == v1) continue;
                if(!g1[v1][i])  continue;
                // g1[v1][i] = TRUE, then check g1[i][v2]
                if(g1[i][v2]) {
                    flag = TRUE;
                    break;
                }
            }
            if(flag)    printf("Y\n");
            else    printf("N\n");
        }
    }
    return 0;
}
