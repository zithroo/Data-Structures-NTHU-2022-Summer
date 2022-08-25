#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_P 5001

int in_deg[MAX_P] = {0}; // indegree
bool visited[MAX_P] = {false};
int total = 0;
bool registered[MAX_P] = {false};

typedef struct cirqueue
{
    int data[MAX_P];
    int front;
    int rear;
} Cirqueue;

void queue_init(Cirqueue *Q);
void queue_push(Cirqueue *Q, int data);
int queue_front(Cirqueue *Q);
void queue_pop(Cirqueue *Q);
bool queue_empty(Cirqueue *Q);
int install(int *adjlist[], int target);
int _remove(int *adjlist[], int target);
void list(int *adjlist[], int n);

int main() {
    int n,q;
    int *adjlist[MAX_P]; // [i][0] records # of adj
    scanf("%d%d", &n, &q);
    // build adjlist
    for(int i = 0; i < n; i++) {
        int mi;
        scanf("%d", &mi);
        adjlist[i] = (int *) malloc((mi + 1) * sizeof(int));
        adjlist[i][0] = mi;
        for(int j = 1; j <= mi; j++)
            scanf("%d", &adjlist[i][j]);
    }
    char cmd[8];
    int target;

    while(q--) {
        scanf("%s", cmd);
        int num;
        if(cmd[0] == 'I') {
            scanf("%d", &target);
            num = install(adjlist, target);
            printf("%d\n", num);
        }
        else if(cmd[0] == 'R') {
            // REMOVE
            scanf("%d", &target);
            num = _remove(adjlist, target);
            printf("%d\n", num);
        }
        else {
            // LIST
            list(adjlist, n);
        }
    }

    // free adjlist
    for(int i = 0; i < n; i++)
        free(adjlist[i]);
    
    return 0;
}

void list(int *adjlist[], int n) {
    printf("%d ", total);
    int count = total;
    for(int i = 0; i < n && count > 0; i++) {
        if(visited[i]) {
            printf("%d ", i);
            count--;
        }
    }
    printf("\n");
}

int _remove(int *adjlist[], int target) {
    int count = 0;
    // reject command
    if(!visited[target])
        return 0;
    if(in_deg[target] != 0)
        return 0;
    
    registered[target] = false;
    Cirqueue que;
    queue_init(&que);
    queue_push(&que, target);
    while(!queue_empty(&que)) {
        int remove = queue_front(&que);
        // printf("remove %d\n", remove);
        queue_pop(&que);
        count++;
        visited[remove] = false;
        for(int i = 1; i <= adjlist[remove][0]; i++) {
            int dependent = adjlist[remove][i];
            in_deg[dependent]--;
            if(in_deg[dependent] == 0 && !registered[dependent])
                queue_push(&que, dependent);
        }
    }
    total -= count;
    return count;
}

int install(int *adjlist[], int target) {
    // return # of install
    int count = 0;
    registered[target] = true;
    if(visited[target])
        return count;
    
    Cirqueue que; // for bfs
    queue_init(&que);

    queue_push(&que, target);
    visited[target] = true;
    count++;

    while(!queue_empty(&que)) {
        int package = queue_front(&que);
        queue_pop(&que);
        for(int i = 1; i <= adjlist[package][0]; i++) {
            int dependent = adjlist[package][i];
            in_deg[dependent]++;
            // printf("from %d add %d\n", package, dependent);
            if(!visited[dependent]) {
                visited[dependent] = true;
                count++;
                // printf("new package %d\n", dependent);
                queue_push(&que, dependent);
            }
        }
    }
    total += count;
    return count;
}

void queue_init(Cirqueue *Q) {
    Q->front = Q->rear = 0;
}
void queue_push(Cirqueue *Q, int data) {
    if((Q->rear + 1) % MAX_P == Q->front) {
        printf("is full\n");
        return;
    }
    Q->rear = (Q->rear + 1) % MAX_P;
    Q->data[Q->rear] = data;
}
int queue_front(Cirqueue *Q) {
    if(Q->front == Q->rear) {
        printf("is empty\n");
        return 0;
    } 
    return Q->data[(Q->front + 1) % MAX_P];
}
void queue_pop(Cirqueue *Q) {
    if(Q->front == Q->rear) {
        printf("is empty\n");
        return;
    }
    Q->front = (Q->front + 1) % MAX_P;
}
bool queue_empty(Cirqueue *Q) {
    return (Q->front == Q->rear);
}