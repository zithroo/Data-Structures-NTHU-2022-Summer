#include <iostream>
#include <stack>
#include <vector>
#include <set>
using namespace std;

int main() {
    int q;
    stack<int> S;
    vector<int> in_stack(200001, 0);
    set<int> not_in_stack;
    for(int i = 1; i <= 200000; i++)
        not_in_stack.insert(i);
    
    cin >> q;
    while(q--) {
        int cmd, x;
        cin >> cmd;
        switch (cmd)
        {
        case 1:
            cin >> x;
            S.push(x);
            if(in_stack[x] == 0) {
                not_in_stack.erase(x);
            }
            in_stack[x]++;
            break;
        case 2:
            if(!S.empty()) {
                int rm = S.top();
                S.pop();
                in_stack[rm]--;
                if(in_stack[rm] == 0) {
                    not_in_stack.insert(rm);
                }       
            }
            break;
        case 3:
            if(!S.empty()) {
                cout << S.top() << endl;
            }
            else {
                cout << "-1" << endl;
            }
            break;
        case 4:
            cout << *not_in_stack.begin() << endl;
            break;
        default:
            break;
        }
    }
    return 0;
}