#include <iostream>
#include <vector>
using namespace std;

struct BinaryMinHeap {
    vector<int> arr;
    BinaryMinHeap();
    bool empty();        // true if size = 0
    size_t size();       // return #elements
    int top();           // return smallest elements
    void push(int x);    // push element
    void pop();          // extract min
    void print();
};
int main() {
    int q, x, cmd;
    cin >> q;
    BinaryMinHeap heap;
    while(q--) {
        cin >> cmd;
        switch (cmd)
        {
        case 1:
            cin >> x;
            heap.push(x);
            break;
        case 2:
            heap.pop();
            break;
        case 3:
            if(heap.empty())    cout << "EMPTY" << endl;
            else    cout << heap.top() << endl;
            break;
        default:
            break;
        }
        // heap.print();
    }
    return 0;
}
BinaryMinHeap:: BinaryMinHeap() {
    arr.emplace_back(-1); // not really use
}

bool BinaryMinHeap::empty() {
    return !size();
}

size_t BinaryMinHeap:: size() {
    return arr.size()-1;
}

int BinaryMinHeap:: top() {
    return arr[1];
}

void BinaryMinHeap:: push(int x) {
    arr.emplace_back(x);
    size_t cur = size();
    while(cur/2) {
        if(x >= arr[cur/2]) break;
        arr[cur] = arr[cur/2];
        cur /= 2;
    }
    arr[cur] = x;
}

void BinaryMinHeap:: pop() {
    if(empty()) return;
    
    int last = arr[size()];
    arr.pop_back();
    int heap_size = size(), cur = 1;
    while(cur * 2 <= heap_size) {
        int next = cur*2;
        if(cur*2+1 <= heap_size && arr[next] > arr[next+1]) next++;
        if(last <= arr[next])   break;
        arr[cur] = arr[next];
        cur = next;
    }
    arr[cur] = last;
}

void BinaryMinHeap::print() {
    cout << "size: " << size() << endl;
    if(empty()) cout << "EMPTY" << endl;
    for(int i = 1; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}