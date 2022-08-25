#include <iostream>
#include <queue>
#include <cstdio>

using namespace std;

inline int nextint() {
	int x = 0, c = getchar(), neg = false;
	while(('0' > c || c > '9') && c!='-' && c!=EOF) c = getchar();
	if(c == '-') neg = true, c = getchar();
	while('0' <= c && c <= '9') x = x*10 + (c^'0'), c = getchar();
	if(neg) x = -x;
	return x; // returns 0 if EOF
}

inline void putint(int x) {
    char arr[10]; // 1~10^8 100000000
    char i;
    arr[9] = 0;
    for(i = 8; i >= 0 && x != 0; i--) {
        arr[i] = x % 10 + '0';
        x /= 10;
    }
    i++;
    fputs(arr+i, stdout);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    priority_queue<int,vector<int>,less<int>> max_heap; // left
    priority_queue<int,vector<int>,greater<int>> min_heap; // right

    int n, median;
    n = nextint();
    int next;
    next = nextint();
    median = next;
    for(int i = 2; i <= n; i++) {
        putint(median); putchar(' ');
        next = nextint();

        if(next < median)
            max_heap.push(next);
        else
            min_heap.push(next);

        int cur_pos = max_heap.size() + 1;
        if(cur_pos > (i+1)/2) { // need to shift left
            min_heap.push(median);
            median = max_heap.top();
            max_heap.pop();
            cur_pos--;
        }
        else if(cur_pos < (i+1)/2) { // need to shift right
            max_heap.push(median);
            median = min_heap.top();
            min_heap.pop();
            cur_pos++;
        }
    }
    putint(median); putchar('\n');
    return 0;
}