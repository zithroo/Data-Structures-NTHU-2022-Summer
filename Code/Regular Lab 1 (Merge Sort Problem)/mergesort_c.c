#include <stdio.h>
#include <stdlib.h>

void merge(long long int array[], int start, int mid, int end) {
    // printf("merge(%d, %d, %d)\n", start, mid, end);
    long long int *buf = (long long int*) malloc((end-start+1) * sizeof(long long int));
    int left = start;
    int right = mid+1;
    int p = 0;
    while(left <= mid && right <= end) {
        if(array[left] >= array[right]) {
            buf[p] = array[left];
            p++;
            left++;
        }
        else {
            buf[p] = array[right];
            p++;
            right++;
        }
    }

    for(; left <= mid; left++, p++)
        buf[p] = array[left];

    for(; right <= end; right++, p++)
        buf[p] = array[right];
        
    for(int i = start; i <= end; i++)
        array[i] = buf[i-start];

    free(buf);
}

void mergesort(long long int array[], int start, int end) {
    // printf("mergesort(%d, %d)\n", start, end);
    if(start >= end)    return;
    int mid = (start + end) / 2;
    mergesort(array, start, mid);
    mergesort(array, mid + 1, end);
    merge(array, start, mid, end);
    return;

}

int main() {
    int n;
    long long int *array;
    scanf("%d", &n);
    array = (long long int*) malloc(n * sizeof(long long int));
    for(int i = 0; i < n; i++)
        scanf("%lld", &array[i]);

    mergesort(array, 0, n - 1);

    for(int i = 0; i < n; i++)
        printf("%lld ", array[i]);
    printf("\n");

    free(array);
    return 0;
}