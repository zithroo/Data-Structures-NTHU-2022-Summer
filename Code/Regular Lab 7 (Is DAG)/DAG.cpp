#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int topology_sort(vector <vector<int> > &adjlist, vector <int> &indegree, queue <int> &Q) {
    int count = 0;
    while(!Q.empty()) {
        int u = Q.front();
        Q.pop();
        count++;
        for(auto v : adjlist[u]) {
            indegree[v]--;
            if(indegree[v] == 0)
                Q.push(v);
        }
    }
    return count;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector <vector<int> > adjlist(n+1);
    vector <int> indegree(n+1, 0);

    int u, v;
    while(m--) {
        cin >> u >> v;
        adjlist[u].emplace_back(v);
        indegree[v]++;
    }

    // scan indegree, and select indegree[i] = 0
    queue <int> Q;
    for(int i = 1; i <= n; i++) {
        if(indegree[i] == 0)
            Q.push(i);
    }

    int count = topology_sort(adjlist, indegree, Q);
    if(count != n)  cout << "NO"<< endl;
    else    cout << "YES" << endl;
    return 0;
}