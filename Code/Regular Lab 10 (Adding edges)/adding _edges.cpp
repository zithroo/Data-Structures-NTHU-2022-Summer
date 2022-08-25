#include <iostream>
#include <vector>

using namespace std;

struct DisjointSet
{
    int n;
    vector<int> parrent, size;
    DisjointSet(int _n);
    int find_root(int x);
    bool same(int x, int y);
    void uni(int x, int y);
};

int largest_size;

int main() {
    int n, m;
    cin >> n >> m;
    largest_size = 1;
    DisjointSet set(n);
    while(m--) {
        int u, v;
        cin >> u >> v;
        set.uni(u, v);
        cout << set.n << " " << largest_size << endl;
    }
    return 0;
}

DisjointSet::DisjointSet(int _n) {
    n = _n;
    parrent.resize(n);
    size.resize(n);
    for(int i = 0; i < n; i++)
        parrent[i] = i;
    fill(size.begin(), size.end(), 1);
}

int DisjointSet::find_root(int x) {
    if(parrent[x] == x) return x;
    else return parrent[x] = find_root(parrent[x]);
}

bool DisjointSet::same(int x, int y) {
    return find_root(x) == find_root(y);
}

void DisjointSet::uni(int x, int y) {
    int root_x = find_root(x);
    int root_y = find_root(y);
    if(root_x == root_y)    return; // same set
    n--;
    if(size[root_x] > size[root_y]) {
        parrent[root_y] = root_x;
        size[root_x] += size[root_y];
        if(largest_size < size[root_x])
            largest_size = size[root_x];
    }
    else {
        parrent[root_x] = root_y;
        size[root_y] += size[root_x];
        if(largest_size < size[root_y])
            largest_size = size[root_y];
    }
}