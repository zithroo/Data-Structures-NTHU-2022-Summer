#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int n, m;

void topo_sort(vector <vector<int>> &adjlist, vector <long long int> &value, vector <int> &indeg) {
    queue <int> Q;
    for(int i = 1; i <= n; i++) {
        if(indeg[i] == 0) {
            Q.push(i);
        }
    }
    while(!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for(auto v : adjlist[u]) {
            indeg[v]--;
            value[v] += value[u];
            if(indeg[v] == 0)
                Q.push(v);
        }
    }
}

int main() {
    cin >> n >> m;
    vector <vector<int>> adjlist(n+1);
    vector <long long int> value(n+1, 0);
    vector <int> indeg(n+1, 0);
    while(m--) {
        char cmd;
        int x1, x2, x3, x4;
        long long int y;
        cin >> cmd;
        switch (cmd)
        {
        case 'A':
            cin >> x1 >> y;
            value[x1] += y;
            break;
        case 'B':
            cin >> x1 >> x2 >> y;
            value[x1] += y;
            adjlist[x2].emplace_back(x1);
            indeg[x1]++;
            break;
        case 'C':
            cin >> x1 >> x2 >> x3 >> y;
            value[x1] += y;
            adjlist[x2].emplace_back(x1);
            adjlist[x3].emplace_back(x1);
            indeg[x1] += 2;
            break;
        case 'D':
            cin >> x1 >> x2 >> x3 >> x4 >> y;
            value[x1] += y;
            adjlist[x2].emplace_back(x1);
            adjlist[x3].emplace_back(x1);
            adjlist[x4].emplace_back(x1);
            indeg[x1] += 3;
            break;
        default:
            break;
        }
    }
    topo_sort(adjlist, value, indeg);

    for(int i = 1; i <= n; i++) {
        if(indeg[i]) {
            cout << "#REF!" << endl;
        }
        else {
            cout << value[i] << endl;
        }
    }
    return 0;
}
/*
    A x1 y         : x1 <- y
    B x1 x2 y      : x1 <- x2 + y
    C x1 x2 x3 y   : x1 <- x2 + x3 + y
    D x1 x2 x3 x4 y: x1 <- x2 + x3 + x4 + y
*/