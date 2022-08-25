#include <iostream>
#include <map>
using namespace std;
using Iter = _Rb_tree_iterator<pair<const int, bool> >;
int main() {
    map <int, bool> BST;
    int n;
    cin >> n;
    while(n--) {
        char cmd;
        int key;
        cin >> cmd >> key;
        switch (cmd)
        {
        case 'I':
            BST.insert(pair<int, bool>(key, true));
            cout << BST.size() << endl;
            break;
        case 'R':
            BST.erase(key);
            cout << BST.size() << endl;
            break;
        case 'S': {
            Iter it = BST.find(key);
            if(it != BST.end())
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
            break;
            }
        case 'L': {
            Iter it = BST.lower_bound(key);
            if(it != BST.end())
                cout << it->first << endl;
            else
                cout << "-1" << endl;
            break;
            }
        case 'U': {
            Iter it = BST.upper_bound(key);
            if(it != BST.end())
                cout << it->first << endl;
            else
                cout << "-1" << endl;
            break;
            }
        default:
            exit(-1);
            break;
        }
    }
    return 0;
}