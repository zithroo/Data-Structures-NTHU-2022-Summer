#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10001

int main() {
    int n;
    char buff[MAX_SIZE], ch;
    scanf("%d", &n);
    ch = getchar();

    while(n--) {
        char *p = buff;
        int flag = 1;

        while((ch = getchar()) != '\n' && ch != EOF) {
            if(flag == 0)   continue;
            if(ch == '(' || ch == '[')
                *p++ = ch;
            else {
                if(ch == ')') {
                    if(p > buff && *(p-1) == '(')   p--;
                    else flag = 0;
                }
                else {
                    // ch = ']'
                    if(p > buff && *(p-1) == '[')   p--;
                    else flag = 0;
                }
            }
        }
        if(p > buff)    flag = 0; // not empty
        if(flag)    printf("Y\n");
        else    printf("N\n");
    }
    return 0;
}