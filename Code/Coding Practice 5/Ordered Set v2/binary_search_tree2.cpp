#include <iostream>
#include <map>
using namespace std;
using Iter = _Rb_tree_iterator<pair<const int, int> >;
int main() {
    map <int, int> BST;
    int n;
    cin >> n;
    while(n--) {
        char cmd;
        int key;
        cin >> cmd >> key;
        switch (cmd)
        {
        case 'I': {
            Iter it = BST.find(key);
            if(it != BST.end()) {
                it->second++;
            }
            else {
                BST.insert(pair<int, bool>(key, 1));
            }
            cout << BST.size() << endl;
            break;
        }
        case 'R': {
            Iter it = BST.find(key);
            if(it != BST.end()) {
                if(it->second > 1)
                    it->second--;
                else
                    BST.erase(it);
            }
            cout << BST.size() << endl;
            break;
        }
        case 'C': {
            Iter it = BST.find(key);
            if(it != BST.end()) {
                cout << it->second << endl;
            }
            else {
                cout << "0" << endl;
            }
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