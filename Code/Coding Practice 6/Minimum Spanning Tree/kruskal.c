#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_V 200002
#define MAX_E 1000000
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

typedef struct disjoint_set {
    int *parrent;
    int size;
} Set;

typedef struct edge
{
    int from, to;
    long long int weight;
} Edge;

void set_init(Set *set, int _size);
int set_find(Set *set, int x);
bool set_same(Set *set, int x, int y);
void set_union(Set *set, int x, int y);
long long int kruskal(Edge *edge_arr, int n, int m);
void adjust(int heap[], int root, int size, Edge edge_arr[]);
void heapsort(int heap[], int size, Edge edge_arr[]);

int main() {
    int n, m;
    Edge *edge_arr; // edge from 1 to m
    scanf("%d%d", &n, &m);
    edge_arr = (Edge *) malloc((m+1) * sizeof(Edge));
    for(int i = 1; i <= m; i++) {
        scanf("%d%d%lld", &edge_arr[i].from, &edge_arr[i].to, &edge_arr[i].weight);
    }
    printf("%lld\n", kruskal(edge_arr, n, m));
    return 0;
}

long long int kruskal(Edge *edge_arr, int n, int m) {
    Set set;
    set_init(&set, n+1);
    // sort edge
    int *edge_index = (int *) malloc((m+1) * sizeof(int)); // max heap
    for(int i = 1; i <= m; i++)
        edge_index[i] = i;
    
    heapsort(edge_index, m, edge_arr);

    long long int sum = 0;
    for(int i = 1; i <= m; i++) {
        int index = edge_index[i];
        if(set_same(&set, edge_arr[index].from, edge_arr[index].to))
            continue;
        set_union(&set, edge_arr[index].from, edge_arr[index].to);
        sum += edge_arr[index].weight;
    }
    return sum;
}

void adjust(int heap[], int root, int size, Edge edge_arr[]) {
    long long int root_key = edge_arr[heap[root]].weight;
    int cur = root;
    int cur_key = heap[root];
    while(cur*2 <= size) {
        int child = cur*2;
        if(child+1 <= size && edge_arr[heap[child]].weight < edge_arr[heap[child+1]].weight)
            child++;
        if(root_key >= edge_arr[heap[child]].weight)  break;
        heap[cur] = heap[child];
        cur = child;
    }
    heap[cur] = cur_key;
}

void heapsort(int heap[], int size, Edge edge_arr[]) {
    for(int i = size/2; i > 0; i--) {
        adjust(heap, i, size, edge_arr);
    }
    
    for(int i = size-1; i > 0; i--) {
        int temp;
        SWAP(heap[1], heap[i+1], temp);
        adjust(heap, 1, i, edge_arr);
    }
}

void set_init(Set *set, int _size) {
    set->parrent = (int *) malloc((_size) * sizeof(int));
    set->size = _size;
    for(int i = 0; i <= _size; i++)
        set->parrent[i] = -1;
}

int set_find(Set *set, int x) {
    if(set->parrent[x] < 0) return x;
    else return set->parrent[x] = set_find(set, set->parrent[x]);
}

void set_union(Set *set, int x, int y) {
    int rx = set_find(set, x);
    int ry = set_find(set, y);
    if(rx == ry)    return;
    set->size--;
    int temp;
    if(set->parrent[rx] < set->parrent[ry]) // -5 vs -3
        SWAP(rx, ry, temp);
    // size of rx < ry, attach rx to ry
    set->parrent[ry] += set->parrent[rx];
    set->parrent[rx] = ry;
}

bool set_same(Set *set, int x, int y) {
    return set_find(set, x) == set_find(set, y);
}