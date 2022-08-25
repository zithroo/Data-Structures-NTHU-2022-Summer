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
    int simple_find(int x);
    int collapsing_find(int x);
    bool same(int x, int y);
    void simple_union(int x, int y);
    void union_bysize(int x, int y);
    void union_byrank(int x, int y);
};

int largest_CC;
int main() {
    int n, m;
    cin >> n >> m;
    DisjointSet set(n);
    largest_CC = 1;
    int u, v;
    while(m--) {
        cin >> u >> v;
        set.union_bysize(u, v);
        cout << set.n << " " << largest_CC << endl;
    }
    return 0;
}

int DisjointSet::simple_find(int x) {
    for(; set[x] > 0; x = set[x]);
    return x;
}

void DisjointSet::simple_union(int x, int y) {
    // int rx = simple_find(x);
    // int ry = simple_find(y);
    int rx = collapsing_find(x);
    int ry = collapsing_find(y);
    if(rx == ry)    return;
    n--;
    set[ry] += set[rx];
    set[rx] = ry;
}

bool DisjointSet::same(int x, int y) {
    // Simple Find
    // return simple_find(x) == simple_find(y);
    // Collapsing_find
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
    if((-set[rx]) > (-set[ry])) swap(rx, ry);
    // size x < size y
    set[ry] += set[rx];
    set[rx] = ry;
    if(largest_CC < (-set[ry])) largest_CC = (-set[ry]);
}

void DisjointSet::union_byrank(int x, int y) {
    int rx = collapsing_find(x);
    int ry = collapsing_find(y);
    if(rx == ry)    return;
    n--;
    if((-set[rx]) > (-set[ry])) swap(rx, ry);
    // rank x < rank y
    if(set[rx] == set[ry])  set[ry]--;
    set[rx] = ry;
}

