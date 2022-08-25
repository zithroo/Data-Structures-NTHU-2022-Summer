#include <iostream>
#define MAX 200001
using namespace std;

int doublelist[MAX], prev_node[MAX], next_node[MAX];
int head, tail;

void reset(int n) {
    head = 1;
    tail = n;
    for(int i = 1; i <= n; i++) {
        next_node[i] = i + 1;
        prev_node[i] = i-1;
    }
    next_node[n] = 1;
    prev_node[1] = n;
}

void print() {
    for(int i = head; i != tail; i = next_node[i])
        cout << doublelist[i] << " ";
    cout << doublelist[tail] << endl;
}

int main() {

    int test_num, n, q;
    char cmd;
    int target;
    for(int i = 1; i < MAX; i++)
        doublelist[i] = i;
    cin >> test_num;
    while(test_num--) {
        cin >> n >> q;
        reset(n);
        // print();
        while(q--) {
            cin >> cmd >> target;
            if(cmd == 'H' && head == target)    continue;
            if(cmd == 'T' && tail == target)    continue;

            int p = prev_node[target];
            int n = next_node[target];
            next_node[p] = next_node[target];
            prev_node[n] = prev_node[target];

            if(cmd == 'H') {
                next_node[target] = head;

                if(target == tail) tail = prev_node[target];
                else prev_node[target] = tail;

                prev_node[head] = target;
                next_node[tail] = target;
                head = target;
                
            }
            else {
                // Inset T
                prev_node[target] = tail;

                if(target == head) head = next_node[target];
                else next_node[target] = head;
                
                next_node[tail] = target;
                prev_node[head] = target;
                tail = target;
            }
            //print();
        }
        print();
    }
    return 0;
}
