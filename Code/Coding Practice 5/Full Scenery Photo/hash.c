#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 1000002
#define BUCKET 3010349
#define TABLESIZE 31250000
// #define BUCKET 13
// #define TABLESIZE 40

int table[TABLESIZE]; // 10e9 / 32 use 1 bit to store number
int hash[BUCKET]; // hadle value of key > 1
int hash_val[BUCKET];
int bit[32];

typedef struct hash_key
{
    int index;
    int bit;
} Key;

typedef struct cirque
{
    int front, rear;
    int frame[MAX];
} Cirque;

Key get_key(int index);
bool test_bit(Key key);
void set_bit(Key key);
void clear_bit(Key key);

bool insert(int index);
bool _remove(int index);
void hash_insert(int index);
void hash_remove(int index);
void queue_init(Cirque *Q);
void queue_push(Cirque *Q, int data);
int queue_pop(Cirque *Q);
Cirque Q;

int main() {
    bit[0] = 1;
    for(int i = 1; i < 32; i++)
        bit[i] = bit[i-1] << 1;
    
    int n, k, rm, count = 0;
    queue_init(&Q);
    scanf("%d%d", &n, &k);
    for(int i = 0; i < k; i++) {
        int key;
        scanf("%d", &key);
        queue_push(&Q, key);
        if(insert(key))
            count++;
    }
    printf("%d ", count);
    int key;
    for(int i = 0; i < n-k; i++) {
        rm = queue_pop(&Q);
        if(_remove(rm))
            count--;
        scanf("%d", &key);
        queue_push(&Q, key);
        if(insert(key))
            count++;
        printf("%d ", count);
    }
    printf("\n");
    return 0;
    
}

Key get_key(int index) {
    Key key;
    key.index = (index-1) >> 5;
    key.bit = (index-1) & (bit[5] - 1);
    return key;
}

bool test_bit(Key key) {
    int b = table[key.index] & bit[key.bit];
    return b;
}

void set_bit(Key key) {
    table[key.index] |= bit[key.bit];
}

void clear_bit(Key key) {
    table[key.index] &= ~bit[key.bit];
}

bool insert(int index) {
    Key key = get_key(index);
    if(!test_bit(key)) {
        set_bit(key);
        // printf("insert set bit: %d\n", index);
        return true;
    }
    // already in hash table
    hash_insert(index);
    return false;
}

void hash_insert(int index) {
    int hashed = index % BUCKET;
    if(!hash[hashed]) {
        hash[hashed] = index;
        hash_val[hashed] = 2;
        // printf("Not use pos and insert exactly two times: %d\n", index);
        return;
    }
    // used by others
    for(int i = 0; i <= (BUCKET-1); i++) {
        if(hash[(hashed+ i) % BUCKET] == index) {
            // change value
            hash_val[(hashed+ i) % BUCKET]++;
            // printf("insert more than two times: %d\n", index);
            return;
        }
        if(!hash[(hashed+ i) % BUCKET]) {
            // insert
            hash[(hashed+ i) % BUCKET] = index;
            hash_val[(hashed+ i) % BUCKET] = 2;
            // printf("Used pos and insert exactly twon times: %d\n", index);
            return;
        }
    }
}

bool _remove(int index) {
    // index must be in table or hash table
    int hashed = index % BUCKET;
    Key key = get_key(index);
    // check if index is in hash table
    for(int i = 0; i <= (BUCKET-1); i++) {
        if(hash[(hashed + i) % BUCKET] == index) {
            // already in hash table
            if(hash_val[(hashed + i) % BUCKET] == 2) {
                hash[(hashed + i) % BUCKET] = 0;
                // printf("In pos: %d , delete to one time %d\n", (hashed + i) % BUCKET, index);
            }
            else { // should be > 2
                hash_val[(hashed + i) % BUCKET]--;
                // printf("In pos: %d , delete to two more time %d\n", (hashed + i) % BUCKET, index);
            }
            break;
        }
        // index register only one time, so it is not in hash table
        if(!hash[(hashed + i) % BUCKET]) {
            clear_bit(key);
            // printf("In pos: %d , clear bit %d\n", (hashed + i) % BUCKET, index);
            return true;
        }
    }
    return false;
}

void queue_init(Cirque *Q) {
    Q->front = Q->rear = 0;
}

void queue_push(Cirque *Q, int data) {
    if(((Q->rear+1) % MAX) != Q->front) {
        Q->rear = (Q->rear+1) % MAX;
        Q->frame[Q->rear] = data;
    }
}

int queue_pop(Cirque *Q) {
    if(Q->front == Q->rear)
        return -1;
    Q->front = (Q->front+1) % MAX;
    return Q->frame[Q->front];
}