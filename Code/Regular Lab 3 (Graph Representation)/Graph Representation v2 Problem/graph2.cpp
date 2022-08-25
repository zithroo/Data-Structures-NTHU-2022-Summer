#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m, q; // |V|, |E|, query lines
    cin >> n >> m >> q;
    vector <vector<int> > adj_list (n + 1); // undirected graph
    vector <int> degree (n + 1, 0);
    int u, v;
    char query;
    while(m--) {
        cin >> u >> v;
        adj_list[u].emplace_back(v);
        adj_list[v].emplace_back(u);
    }

    while(q--) {
        cin >> query;
        cin >> u;
        if(query == 'D') {
            /* D u : Asking the degree of vertex uu in graph GG . Print the degree in a line. */
            cout << adj_list[u].size() << endl;
        }
        else {
            /* N u v : Asking if uu, vv are neighboring vertices in graph GG . If yes, print a line "Y". Otherwise, print a line "N". */
            cin >> v;
            bool flag = false;
            for(auto i = adj_list[u].begin(); i != adj_list[u].end(); i++) {
                if(*i == v) {
                    flag = true;
                    break;
                }
            }
            if(flag)
                cout << "Y" << endl;
            else
                cout << "N" << endl;
        }
    }
    return 0;
}
