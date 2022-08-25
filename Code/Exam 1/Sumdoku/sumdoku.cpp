#include <iostream>
#include <vector>
#define MAX_CAGE 82
using namespace std;

struct element
{
    int x, y;
};
int matrix[10][10];
bool repeat[10];

bool check_row() {
    for(int i = 1; i <= 9; i++) {
        fill(repeat, repeat + 10, false);
        for(int j = 1; j <= 9; j++) {
            if(repeat[matrix[i][j]])
                return false;
            repeat[matrix[i][j]] = true;
        }
    }
    return true;
}

bool check_col() {
    for(int i = 1; i <= 9; i++) {
        fill(repeat, repeat + 10, false);
        for(int j = 1; j <= 9; j++) {
            if(repeat[matrix[j][i]])
                return false;
            repeat[matrix[j][i]] = true;
        }
    }
    return true;
}

bool check_block() {
    for(int i = 1; i <= 7; i+=3) {
        for(int j = 1; j <= 7; j += 3) {
            fill(repeat, repeat + 10, false);
            for(int a = i; a < i+3; a++) {
                for(int b = j; b < j+3; b++) {
                    // cout << matrix[a][b] << " ";
                    if(repeat[matrix[a][b]])
                        return false;
                    repeat[matrix[a][b]] = true;
                }
            }
        }
    }
    return true;
}

bool check_cage(vector <vector <element>> &cage, int *cage_restrict, int cage_num) {
    for(int i = 1; i <= cage_num; i++) {
        int sum = 0;
        for(auto it = cage[i].begin(); it != cage[i].end(); it++) {
            sum += matrix[(*it).x][(*it).y];
        }
        if(sum != cage_restrict[i])
            return false;
    }
    return true;
}

int main() {
    int test_num;
    int cage_num, cage_restrict[MAX_CAGE];
    cin >> test_num;
    
    while(test_num--) {
        cin >> cage_num;
        for(int i = 1; i <= cage_num; i++)
            cin >> cage_restrict[i];

        vector <vector <element>> cage(cage_num+1);
        for(int i = 1; i <= 9; i++) {
            for(int j = 1; j <= 9; j++) {
                int cage_index;
                cin >> cage_index;
                element temp;
                temp.x = i;
                temp.y = j;
                cage[cage_index].emplace_back(temp);
            }
        }
        
        for(int i = 1; i <= 9; i++)
            for(int j = 1; j <= 9; j++)
                cin >> matrix[i][j];
        
        // if(!check_row())    cout << "row err" << endl;
        // if(!check_col())    cout << "col err" << endl;
        // if(!check_block())  cout << "block err" << endl;
        // if(!check_cage(cage, cage_restrict, cage_num))  cout << "cage err" << endl;
        if(check_row() && check_col() && check_block() && check_cage(cage, cage_restrict, cage_num))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    return 0;
}