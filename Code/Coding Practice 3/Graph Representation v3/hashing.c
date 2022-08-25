#include <stdio.h>
#include <stdlib.h>

#define BUCKET 1398269
#define NUM 100000

int degree[100001];
long long int hash_table[BUCKET];

int hash(long long int a, long long int b, long long int *value) {
    if(a < b)
        *value = NUM * a + b;
    else
        *value = NUM * b + a;
    // printf("%lld = NUM * %lld + %lld \n", *value, a, b);
    return (*value) % BUCKET;
}


int main() {
    int n, m, q;
    long long int v1, v2;
    scanf("%d%d%d", &n, &m, &q);
    char cmd;
    long long int value = 0;
    int index;

    while(m--) {
        scanf("%lld%lld", &v1, &v2);
        degree[v1]++;
        degree[v2]++;
        /* hashing */
        index = hash(v1, v2, &value);
        // printf("index: %d\n", index);
        if(!hash_table[index])  hash_table[index] = value;
        else {
            for(int i = 1; i <= (BUCKET-1)/2; i++) {
                if(!hash_table[(index + i * i % BUCKET) % BUCKET]) {
                    hash_table[(index + i * i % BUCKET) % BUCKET] = value;
                    break;
                }
            }
        }
    }

    while(q--) {
        scanf(" %c", &cmd);
        if(cmd == 'D') {
            scanf("%lld", &v1);
            printf("%d\n", degree[v1]);
        }
        else {
            scanf("%lld%lld", &v1, &v2);
            /* search hash table */
            index = hash(v1, v2, &value);

            if(!hash_table[index])  printf("N\n");
            else if(hash_table[index] == value) printf("Y\n");
            else {
                int flag = 0;
                for(int i = 1; i <= (BUCKET-1)/2; i++) {
                    if(!hash_table[(index + i * i % BUCKET) % BUCKET])   break;
                    else if(hash_table[(index + i * i % BUCKET) % BUCKET] == value) {
                        flag = 1;
                        break;
                    }
                }
                if(flag)    printf("Y\n");
                else printf("N\n");
            }
        }
    }
    return 0;
}