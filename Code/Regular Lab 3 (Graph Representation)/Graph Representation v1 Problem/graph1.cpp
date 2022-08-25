#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m, q; /* |V|, |E|, query lines */
    cin >> n >> m >> q;
    vector <vector<int> > adj_matrix (n + 1, vector<int>(n + 1, 0)); /* undirected graph */
    int u, v;
    char query;
    while(m--) {
        cin >> u >> v;
        adj_matrix[u][v] = 1;
        adj_matrix[v][u] = 1;
        adj_matrix[u][0]++; /* use [u][0] to record degree */
        adj_matrix[v][0]++;
    }

    while(q--) {
        cin >> query;
        cin >> u;
        if(query == 'D') {
            /* D u : Asking the degree of vertex uu in graph GG . Print the degree in a line. */
            cout << adj_matrix[u][0] << endl;
        }
        else {
            /* N u v : Asking if u, v are neighboring vertices in graph G . If yes, print a line "Y". Otherwise, print a line "N". */
            cin >> v;
            if(adj_matrix[u][v])
                cout << "Y" << endl;
            else
                cout << "N" << endl;
        }
    }
    return 0;
}
