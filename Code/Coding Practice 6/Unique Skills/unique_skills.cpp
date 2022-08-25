#include <iostream>
#include <map>
#include <vector>

using namespace std;
using Iter = _Rb_tree_iterator<pair<const int, int> >;

int main() {
    int n, m, q; // # of player, # of books, # of query
    cin >> n >> m >> q;

    vector <int> copy(m+1);
    vector <vector<bool> > players_skill(n+1, vector<bool>(m+1, false));
    vector <vector<int>> players_status(n+1, vector<int>(2, 0)); // first: level, second: # of skill
    vector <map<int, int>> steal(m+1); // first: level, second: playerID

    for(int i = 1; i <= n; i++)
        cin >> players_status[i][0];
    for(int i = 1; i <= m; i++)
        cin >> copy[i];
    
    for(int i = 1; i <= q; i++) {
        int player, book;
        cin >> player >> book;
        if(players_skill[player][book]) {
            cout << players_status[player][1] << endl;
            continue;
        }

        if(copy[book] > 0) {
            players_status[player][1]++;
            players_skill[player][book] = true;
            copy[book]--;
            steal[book].insert(pair<int, int>(players_status[player][0], player));
        }
        else { // steal from others
            Iter it = steal[book].upper_bound(players_status[player][0]);
            int target;
            if(it == steal[book].end()) it--;
            target = it->second;
            steal[book].erase(it);
            
            players_status[target][1]--;
            players_skill[target][book] = false;

            players_status[player][1]++;
            players_skill[player][book] = true;
            steal[book].insert(pair<int, int>(players_status[player][0], player));
        }
        cout << players_status[player][1] << endl;
    }

    for(int i = 1; i <= n; i++) {
        cout << players_status[i][1] << " ";
        for(int j = 1; j <= m; j++) {
            if(players_skill[i][j])
                cout << j << " ";
        }
        cout << endl;
    }
    return 0;
}