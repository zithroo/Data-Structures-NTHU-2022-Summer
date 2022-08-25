#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, m, q;
    int v1, v2;
    char cmd;
    cin >> n >> m >> q;
    vector <vector<int> > adjlist(n+1);

    while(m--) {
        cin >> v1 >>  v2;
        adjlist[v1].emplace_back(v2);
        adjlist[v2].emplace_back(v1);
    }
    /* sort list and use binary search */
    for(int i = 1; i <= n; i++)
        sort(adjlist[i].begin(), adjlist[i].end());
    
    while(q--) {
        cin >> cmd >> v1;
        if(cmd == 'D') {
            cout << adjlist[v1].size() << endl;
        }
        else {
            cin >> v2;
            if(binary_search(adjlist[v1].begin(), adjlist[v1].end(), v2))    cout << "Y" << endl;
            else cout << "N" << endl;
        }
    }
    
    return 0;
}