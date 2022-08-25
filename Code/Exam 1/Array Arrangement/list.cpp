#include <iostream>
#include <list>
#include <vector>
using namespace std;

int main() {
    int test_num;
    char cmd;
    int target;
    
    cin >> test_num;
    while(test_num--) {
        int n, q;
        cin >> n >> q;
        list <int> arr;
        vector <list<int>::iterator> position(1);

        for(int i = 1; i <= n; i++)
            arr.push_back(i);
        
        for(auto it = arr.begin(); it != arr.end(); it++) {
            position.emplace_back(it);
        }

        while(q--) {
            cin >> cmd >> target;
            if(cmd == 'H') {
                arr.erase(position[target]);
                arr.emplace_front(target);
                position[target] = arr.begin();
            }
            else {
                arr.erase(position[target]);
                arr.emplace_back(target);
                position[target] = prev(arr.end());
            }
        }
        
        for(auto it: arr)
            cout << it << " ";
        cout << "\n";
    }
}