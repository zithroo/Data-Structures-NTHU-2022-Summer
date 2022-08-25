#include <iostream>
#include <algorithm>
#include <unordered_set>

using namespace std;
using LL = long long int;

LL num(LL v, LL u)
{
  return max(v, u)*100000 + min(v, u);
}

int main(){
    LL n, m, q; 
    cin>>n>>m>>q;
    vector<int> degree (n+1, 0);
    unordered_set<LL> hash ;
    while(m--) {
        LL v, u;
        cin >> v >> u;
        hash.insert(num(v, u));
        degree[v]++;
        degree[u]++;
    }

    while(q--) {
        string cmd;
        cin >> cmd;
        if (cmd == "D") {
            LL i;
            cin >> i;
            cout << degree[i] << endl;
        }
        else {
            LL v, u;
            cin >> v >> u;
            if(hash.find(num(v, u)) != hash.end()) {
                cout << "Y" << endl;
            }
            else
                cout << "N" << endl;
        }
    }
}