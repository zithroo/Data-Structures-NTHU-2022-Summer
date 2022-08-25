#include <iostream>
#include <map>
#include <math.h>

using namespace std;
using Iter = _Rb_tree_iterator<pair<const int, int> >;

void insert(map<int, int> &RB, int key) {
    Iter iter = RB.find(key);
    if(iter != RB.end())
        iter->second++;
    else
        RB.insert(pair<int, int>(key, 1));
}

void remove(map<int, int> &RB, int key) {
    Iter iter = RB.find(key);
    if(iter != RB.end()) {
        if(iter->second > 1)
            iter->second--;
        else
            RB.erase(iter);
    }
}

int difference(map<int, int> &Largest, map<int, int> &Smallest) {
    if(Largest.size() == 0 || Smallest.size() == 0)
        return -1;
    int l = Largest.rbegin()->first;
    int s = Smallest.begin()->first;
    return abs(l-s);
}

int main() {
    map<int, int> RB_odd, RB_even;
    int n, q;
    cin >> n >> q;
    while(n--) {
        int key;
        cin >> key;
        if(key % 2 != 0)
            insert(RB_odd, key);
        else
            insert(RB_even, key);
    }
    while(q--) {
        int cmd, key;
        cin >> cmd;
        switch (cmd)
        {
        case 1: // Add number x
            cin >> key;
            if(key % 2 != 0)
                insert(RB_odd, key);
            else
                insert(RB_even, key);
            break;

        case 2: // Delete number x. Ignore this operation if x is not present.
            cin >> key;
            if(key % 2 != 0)
                remove(RB_odd, key);
            else
                remove(RB_even, key);
            break;

        case 3: // Report the absolute difference between the largest odd number and the smallest even number
        {   int result_3 = difference(RB_odd, RB_even);
            if(result_3 == -1)  cout << "QQ" << endl;
            else    cout << result_3 << endl;
            break;
        }
        case 4: // Report the absolute difference between the smallest odd number and the largest even number
        {
            int result_4 = difference(RB_even, RB_odd);
            if(result_4 == -1)  cout << "QQ" << endl;
            else    cout << result_4 << endl;
            break;
        }
        default:
            break;
        }
    }
    
    return 0;
}