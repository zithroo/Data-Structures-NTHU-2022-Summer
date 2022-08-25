#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool many = false;
void bfs(vector<vector<int>> &adjlist, vector<int> &label, int root) {
    queue <int> Q;
    Q.push(root);
    label[root] = 1;
    while(!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for(auto v: adjlist[u]) {
            if(!label[v]) {
                if(label[u] == 1)
                    label[v] = 2;
                else
                    label[v] = 1;
                Q.push(v);
            }
            else {
                // adjacent node is labeled
                if(label[u] == label[v]) {
                    many = true;
                    return;
                }
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector <vector<int>> adjlist(n+1);
    vector <int> label (n+1, 0); // 0:unvisited  1: one, 2: two
    while(m--) {
        int u, v;
        cin >> u >> v;
        adjlist[u].emplace_back(v);
        adjlist[v].emplace_back(u);
    }
    
    for(int i = 1; i <= n; i++) {
        if(!label[i] && !many) {
            bfs(adjlist, label, i);
        }
    }
    if(many) {
        cout << "MANY" << endl;
    }
    else {
        for(int i = 1; i <= n; i++) {
            cout << label[i] << " ";
        }
        cout << endl;
    }

    return 0;
}