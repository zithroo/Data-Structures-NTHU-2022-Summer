#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    priority_queue <int, vector<int>, greater<int>> pq; // min heap use greater
    int q;
    cin >> q;
    int cmd, x;
    while(q--) {
        cin >> cmd;
        switch (cmd)
        {
        case 1:
            cin >> x;
            pq.push(x);
            break;
        case 2:
            if(!pq.empty())
                pq.pop();
            break;
        case 3:
            if(pq.empty())  cout << "EMPTY" << endl;
            else  cout << pq.top() << endl;
            break;
        default:
            break;
        }
    }
    return 0;
}