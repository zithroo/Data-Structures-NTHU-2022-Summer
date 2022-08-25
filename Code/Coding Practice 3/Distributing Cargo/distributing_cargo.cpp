#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct element
{
    int to;
    int broken;
    element(int _to, int _broken): to(_to), broken(_broken) {}
};

int main() {
    int n;
    cin >> n;
    
    vector <vector <element> > adjlist(n + 1);
    vector <long long int> broken(n + 1, 0);
    vector <bool> is_visited(n + 1, false);
    stack <int> s;

    for(int i = 1; i < n; i++) {
        int v1, v2, b;
        cin >> v1 >> v2 >> b;
        adjlist[v1].emplace_back(element (v2, b));
        adjlist[v2].emplace_back(element (v1, b));
    }
    
    // DFS
    s.push(1);
    is_visited[1] = true;
    while(!s.empty()) {
        int u = s.top();
        s.pop();
        for(auto element_v : adjlist[u]) {
            if(!is_visited[element_v.to]) {
                is_visited[element_v.to] = true;
                s.push(element_v.to);
                broken[element_v.to] = broken[u] + element_v.broken;
            }
        }
    }

    for(int i = 1; i <= n; i++) {
        if(adjlist[i].size() == 1)
            cout << "City " << i << ": " << broken[i] << endl;
    }

    return 0;
}