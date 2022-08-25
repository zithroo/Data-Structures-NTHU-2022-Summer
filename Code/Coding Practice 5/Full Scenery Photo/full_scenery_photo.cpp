#include <iostream>
#include <unordered_map>
#define MAX 1000002

using namespace std;
using Iter = unordered_map<int, int>::iterator;
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

void insert(unordered_map<int, int> &Hash, int key) {
    Iter it = Hash.find(key);
    if(it != Hash.end()) {
        it->second++;
    }
    else {
        Hash.insert(pair<int, int>(key, 1));
    }
}

void remove(unordered_map<int, int> &Hash, int key) {
    Iter it = Hash.find(key);
    if(it != Hash.end()) {
        if(it->second > 1)
            it->second--;
        else
            Hash.erase(it);
    }
}

Cirqueue Q;

int main() {
    unordered_map<int, int> Hash;
    int n, k, rm;
    cin >> n >> k;
    for(int i = 0; i < k; i++) {
        int key;
        cin >> key;
        Q.push(key);
        insert(Hash, key);
    }
    cout << Hash.size() << " ";

    for(int i = 0; i < n-k; i++) {
        rm = Q.get_front();
        Q.pop();
        remove(Hash, rm);
        int key;
        cin >> key;
        Q.push(key);
        insert(Hash, key);
        cout << Hash.size() << " ";
    }
    cout << endl;
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