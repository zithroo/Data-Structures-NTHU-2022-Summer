#include <iostream>
#include <list>
#define COUNT 2

using namespace std;
using Iter = list<int>::iterator;

int main() {
    list<int> cirlist;
    Iter iter;
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++)
        cirlist.emplace_back(i);
    iter = cirlist.begin();

    while(n--) {
        for(int i = 1; i < COUNT; i++) {
            iter = (next(iter) == cirlist.end()) ? cirlist.begin(): next(iter);
        }
        cout << *iter << " ";
        Iter del = iter;
        iter = (next(iter) == cirlist.end()) ? cirlist.begin(): next(iter);
        cirlist.erase(del);
    }
    cout << endl;
    return 0;
}