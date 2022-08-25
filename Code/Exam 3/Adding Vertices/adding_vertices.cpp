#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct DisjointSet
{
    int n;
    // if set[i] < 0, i is root, and -set[i] is size, if set[i] >= 0, set[i] is parrent
    vector<int> set;
    DisjointSet(int _n) : n(_n), set(n, -1) {};
    int collapsing_find(int x);
    bool same(int x, int y);
    void union_bysize(int x, int y);
};

int num_of_CC = 0;
int largeCC = 1;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int> > adjlist(n+1);
    DisjointSet set(n+1);
    vector<bool> visited(n+1, false);

    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adjlist[u].emplace_back(v);
        adjlist[v].emplace_back(u);
    }
    int root;
    for(int i = 1; i <= n; i++) {
        cin >> root;
        visited[root] = true;
        num_of_CC++;
        for(auto v : adjlist[root]) {
            if(!visited[v]) continue;
            set.union_bysize(root, v);
        }
        cout << num_of_CC << " " << largeCC << endl;
    }
    return 0;
}


bool DisjointSet::same(int x, int y) {
    return collapsing_find(x) == collapsing_find(y);
}

int DisjointSet::collapsing_find(int x) {
    return set[x]<0 ? x: set[x] = collapsing_find(set[x]);
}

void DisjointSet::union_bysize(int x, int y) {
    int rx = collapsing_find(x);
    int ry = collapsing_find(y);
    if(rx == ry)    return;
    n--;
    num_of_CC--;
    if((-set[rx]) > (-set[ry])) swap(rx, ry);
    // size x < size y
    set[ry] += set[rx];
    set[rx] = ry;
    if(largeCC < (-set[ry])) largeCC = (-set[ry]);
}


