#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Vector
{
    int size;
    int *data;
    int capacity;
} vector;

void vector_init(vector *v, int size);
void vector_delete(vector *v);
void resize(vector *v);
void vector_push(vector *v, int data);
void vector_pop(vector *v);
void dfs(vector *adjlist, int *visited, vector *topo_order, int root, int *time);
bool cycle = false;

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector *adjlist = (vector *) malloc((n+1) * sizeof(vector));
    for(int i = 0; i < n+1; i++)
        vector_init(&adjlist[i], 0);
    
    while(m--) {
        int u, v;
        scanf("%d%d", &u, &v);
        vector_push(&adjlist[u], v);
    }
    
    vector topo_order;
    vector_init(&topo_order, n);
    int *visited = (int *) malloc((n+1) * sizeof(int)); // 0 unvisit, 1 visited, -1 finished
    for(int i = 1; i <= n; i++)
        visited[i] = 0;

    int time = 0;
    for(int i = 1; i <= n; i++) {
        if(!visited[i]) {
            dfs(adjlist, visited, &topo_order, i, &time);
            time++;
        }
    }

    // for(int i = topo_order.size - 1; i >= 0; i--) {
    //     printf("%d ", topo_order.data[i]);
    // }
    // printf("\n");
    
    if(cycle)
        printf("NO\n");
    else
        printf("YES\n");

    for(int i = 0; i < n+1; i++)
        vector_delete(&adjlist[i]);
    free(adjlist);

    return 0;
}

void dfs(vector *adjlist, int *visited, vector *topo_order, int root, int *time) {
    visited[root] = 1;
    // printf("start| root: %d  %d\n", root, *time);
    for(int i = 0; i < adjlist[root].size; i++) {
        int next = adjlist[root].data[i];
        if(visited[next] == 1) {
            cycle = true;
        }
        if(!visited[next]) {
            (*time)++;
            // printf("from %d visit %d\n", root, next);
            dfs(adjlist, visited, topo_order, next, time);
        }
    }
    (*time)++;
    // printf("finish| root: %d  %d\n", root, *time);
    vector_push(topo_order, root);
    visited[root] = -1;
}

void vector_init(vector *v, int capacity) {
    v->capacity = capacity ? capacity : 8;
    v->size = 0;
    v->data = (int *) malloc(capacity * sizeof(int));
    if(v->data == NULL) {
        fprintf(stderr, "fail to allocate meomry in vector_init");
        exit(EXIT_FAILURE);
    }
}

void vector_delete(vector *v) {
    free(v->data);
    v->data = NULL;
    v->capacity = 0;
    v->size = 0;
}

void vector_resize(vector *v) {
    int new_cap = v->capacity * 2;
    int *new_ptr = (int*) realloc(v->data, new_cap * sizeof(int));
    if(new_ptr == NULL) {
        fprintf(stderr, "fail to realloc in vector_resize");
        exit(-1);
    }
    v->data = new_ptr;
    v->capacity = new_cap;
}

void vector_push(vector *v, int data) {
    if(v->size == v->capacity) {
        vector_resize(v);
    }
    v->data[v->size++] = data;
}

void vector_pop(vector *v) {
    if(v->size == 0) {
        fprintf(stderr, "fail to pop empty vector");
        exit(-1);
    }
    v->size--;
}

int vector_top(vector *v) {
    if(v->size == 0) {
        fprintf(stderr, "fail to get top in empty vector");
        exit(-1);
    }
    return v->data[v->size - 1];
}
