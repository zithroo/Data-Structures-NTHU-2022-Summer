#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void dfs(vector <vector<int> > &graph, vector <bool> &is_visited, int root) {
    is_visited[root] = true;
    for(auto i : graph[root]) {
        if(!is_visited[i]) dfs(graph, is_visited, i);
    }
}

void bfs(vector <vector<int> > &graph, vector <bool> &is_visited, int root) {
    queue <int> q;
    is_visited[root] = true;
    q.push(root);
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        for(auto v : graph[u]) {
            if(!is_visited[v])  {is_visited[v]= true; q.push(v);}
        }
    }
}

int main() {
    int test_num, n, m;
    cin >> test_num;
    while(test_num--) {
        cin >> n >> m;
        vector <vector<int> > graph(n+1);
        vector <bool> is_visited(n+1);
        int count = 0;
        while(m--) {
            int v1, v2;
            cin >> v1 >> v2;
            graph[v1].emplace_back(v2);
            graph[v2].emplace_back(v1);
        }
        for(int i = 1; i <= n; i++) {
            if(!is_visited[i]) {
                count++;
                bfs(graph, is_visited, i);
            }
        }
        cout << count << endl;
    }
    return 0;
}