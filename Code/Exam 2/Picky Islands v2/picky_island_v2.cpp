#include <iostream>
#include <vector>
using namespace std;

/* edges is the 2*edges of the connected component, and dfs return the number of nodes */
int dfs(vector <vector<int> > &adjlist, vector <bool> &is_visited, int root, int* edges) {
    int count = 0;
    is_visited[root] = true;
    for(auto v : adjlist[root]) {
        if(!is_visited[v]) {
            count += dfs(adjlist, is_visited, v, edges);
        }
    }
    *edges += adjlist[root].size();
    return count + 1;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector <vector<int> > adjlist(n+1);
    vector <bool> is_visited(n+1, false);

    while(m--) {
        int v1, v2;
        cin >> v1 >> v2;
        adjlist[v1].emplace_back(v2);
        adjlist[v2].emplace_back(v1);
    }

    for(int i = 1; i <= n; i++) {
        if(!is_visited[i]) {
            int edges = 0;
            int num_of_node = dfs(adjlist, is_visited, i, &edges);
            cout << i << " ";
            if((edges/2) > (num_of_node-1)) {
                cout << "YES" << endl;
            }
            else {
                cout << "NO" << endl;
            }
        }
    }

    return 0;
}

/*
 * Assume that there are n nodes.
 * if |E| > n-1, the graph has at least a cycle, that means u to v has different path
 */