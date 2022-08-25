#include <iostream>
#include <vector>
#include <queue>
using namespace std;

char direction[4] = {'U', 'R', 'L', 'D'};
int dir[4][2] = {{-1, 0}, {0, 1}, {0, -1}, {1, 0}};

struct Coordinate
{
    int x;
    int y;
    Coordinate(int _x, int _y) :
        x(_x), y(_y) {}
};

void print(vector <vector <char>> &maze) {
    for(auto i : maze) {
        for(auto j : i)
            cout << j;
        cout << endl;
    }
}

int main() {
    int W, L; // W*L maze
    cin >> W >> L;
    Coordinate start(0, 0), end(0, 0);
    vector <vector <char>> maze(W+2, vector<char> (L+2, '#')); // padding with wall
    
    for(int i = 1; i <= W; i++) {
        for(int j = 1; j <= L; j++) {
            cin >> maze[i][j];
            if(maze[i][j] == 'A') {
                start.x = i;
                start.y = j;
            }
            if(maze[i][j] == 'B') {
                end.x = i;
                end.y = j;
            }
        }
    } 

    // BFS
    queue <Coordinate> Q;
    Q.push(Coordinate(start));

    while(!Q.empty()) {
        Coordinate now = Q.front();
        Q.pop();
        for(int i = 0; i < 4; i++) {
            Coordinate next(now.x + dir[i][0], now.y + dir[i][1]);
            if(maze[next.x][next.y] == '.') {
                // can walk and not visites
                maze[next.x][next.y] = 4-i-1; // if direction is left, maze[next] = R
                Q.push(Coordinate(next.x, next.y));
            }
            else if(maze[next.x][next.y] == 'B') {
                 maze[next.x][next.y] = 4-i-1;
                 break;
            }
        }
    }
    if(maze[end.x][end.y] == 'B') {
        cout << "NO" << endl;
        return 0;
    }

    // there is a way
    vector<char> path;
    Coordinate iter(end.x, end.y);
    while(maze[iter.x][iter.y] != 'A') {
        int dir_index = maze[iter.x][iter.y];
        path.emplace_back(direction[4 - dir_index - 1]);
        iter.x += dir[dir_index][0];
        iter.y += dir[dir_index][1];
    }
    cout << "YES" << endl;
    cout << path.size() << endl;
    for(auto it = path.rbegin(); it != path.rend(); it++)
        cout << *it;
    cout << endl;
    return 0;
}