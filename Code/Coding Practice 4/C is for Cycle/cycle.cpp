#include <iostream>
#include <vector>
#include <stack>
using namespace std;
struct Cycle
{
    int head;
    int tail;
    Cycle(int _h, int _t) :
        head(_h), tail(_t) {}
};


Cycle DFS(vector<vector<int>> &adjlist, vector<int> &visited, int root) {
    stack <int> S;
    S.push(root);
    visited[root] = -1;
    while(!S.empty()) {
        int u = S.top();
        S.pop();
        for(auto v : adjlist[u]) {
            if(!visited[v]) {
                visited[v] = u;
                S.push(v);
            }
            else if(visited[v] && v != visited[u]) {
                // cycle
                Cycle c(visited[v], v);
                visited[v] = u;
                return c;
            }
        }
    }
    return Cycle (0, 0);
}

int main() {
    int n, m;
    cin >> n >> m;
    vector <vector<int> > adjlist(n+1);
    vector <int> visited(n+1, 0); // store prev node, if node is root => visited[root] = -1

    while(m--) {
        int u, v;
        cin >> u >> v;
        adjlist[u].emplace_back(v);
        adjlist[v].emplace_back(u);
    }
    // DFS
    Cycle c(0, 0);
    for(int i = 1; i <= n; i++) {
        if(!visited[i])
            c = DFS(adjlist, visited, i);
        if(c.head)
            break;
    }

    if(!c.head)  cout << "IMPOSSIBLE" << endl;
    else {
        int it = c.tail;
        vector <int> cycle;
        while(it != c.head) {
            cycle.emplace_back(it);
            it = visited[it];
        }
        cycle.emplace_back(it);
        cout << cycle.size() << endl;
        for(auto i : cycle)
            cout << i << " ";
        cout << endl;
    }

    return 0;
}