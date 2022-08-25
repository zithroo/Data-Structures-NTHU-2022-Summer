#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#define MAX 1000002

using namespace std;
using Iter = multiset<int>::iterator;

struct Cirqueue
{
    int front, rear;
    int frame[MAX];
    Cirqueue () : front(0), rear(0) {}
    bool empty();
    void push(int data);
    void pop();
    int get_front();
};

int get_mid(int k) {
    int ans = (k+1)/2;
    if(k % 2 == 0)
        ans++;
    return ans;
}

Cirqueue Q;
int main() {
    int n, k, median, rm, position;
    multiset<int> tree;
    Iter iter;

    cin >> n >> k;
    for(int i = 1; i <= k; i++) {
        int in;
        cin >> in;
        Q.push(in);
        tree.insert(in);
    }

    position = get_mid(k);
    iter = tree.begin();
    advance(iter, position-1);
    median = *iter;

    for(int i = 0; i < n-k; i++) {
        cout << median << " ";

        rm = Q.get_front();
        Q.pop();
        int in;
        cin >> in;
        Q.push(in);

        tree.insert(in);
        int move = 0;
        if(k % 2 == 0 && in < median)
            move = -1;
        else if(k % 2 == 1 && in >= median)
            move = 1;

        advance(iter, move);
        median = *iter;

        move = 0;
        if(k % 2 == 0 && (rm <= median || iter == tree.find(rm)))
            move = 1;
        else if(k % 2 == 1 && (rm > median || iter == tree.find(rm)))
            move = -1;
        advance(iter, move);
        tree.erase(tree.find(rm));
        median = *iter;
    }
    cout << median << "\n";
    return 0;
}

bool Cirqueue:: empty() {
    return (front == rear);
}

void Cirqueue:: push(int data) {
    if((rear+1) % MAX == front) {
        cout << "push err" << endl;
        exit(-1);
    }
    rear = (rear+1) % MAX;
    frame[rear] = data;
}

void Cirqueue:: pop() {
    if(front == rear) {
        cout << "pop err" << endl;
        exit(-1);
    }
    front = (front+1) % MAX;
}

int Cirqueue:: get_front() {
    if(front != rear)
        return frame[(front+1) % MAX];
    return 0;
}