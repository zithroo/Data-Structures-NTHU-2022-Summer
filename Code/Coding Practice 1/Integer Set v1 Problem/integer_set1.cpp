#include <iostream>
#include <set>
using namespace std;

int main() {
    multiset<long long int> set;
    int n;
    long long int key;
    char cmd;
    cin >> n;
    while(n--) {
        cin >> cmd >> key;
        switch (cmd)
        {
        case 'I':
            set.insert(key);
            break;
        case 'R':
        {
            multiset<long long int>::iterator it = set.find(key);
            if(it != set.end())
                set.erase(it);
            break;
        }
        case 'C':
            cout << set.count(key) << endl;
            break;
        default:
            cout << "error cmd" << endl;
            exit(-1);
            break;
        }
    }
    return 0;
}