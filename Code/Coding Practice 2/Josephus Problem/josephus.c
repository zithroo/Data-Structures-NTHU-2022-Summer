#include <stdio.h>
#include <stdlib.h>
#define MAX 200001
#define COUNT 2
int main() {
    int cirqueue[MAX], n;
    int cur, pre;
    scanf("%d", &n);
    // cirqueue = next (use array to implement linked list)
    cirqueue[0] = 1;
    cirqueue[n] = 1;
    for(int i = 1; i < n; i++)
        cirqueue[i] = i + 1;
    
    cur = 0;
    while(n--) {
        for(int i = 1; i <= COUNT; i++) {
            pre = cur;
            cur = cirqueue[cur]; // cur = cur->next
        }
        // delete
        printf("%d ", cur);
        cirqueue[pre] = cirqueue[cur];
    }
    printf("\n");
    return 0;
}