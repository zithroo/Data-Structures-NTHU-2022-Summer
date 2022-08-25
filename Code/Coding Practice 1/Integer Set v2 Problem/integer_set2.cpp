#include <iostream>
#define MAX 1000001

using namespace std;

int main() {
    int *set = new int [MAX];
    int n, parameter;
    char cmd;
    for(int i = 0; i < MAX; i++)
        set[i] = 0;
    cin >> n;
    while(n--) {
        cin >> cmd >> parameter;
        switch (cmd)
        {
        case 'I':
            set[parameter]++;
            break;
        case 'R':
            if(set[parameter] > 0)  set[parameter]--;
            break;
        case 'C':
            cout << set[parameter] << endl;
            break;
        default:
            cout << "error cmd" << endl;
            break;
        }
    }
    return 0;
}
/*
I ii : Insert. Insert one integer ii to the integer set.
R ii : Remove. Remove one integer ii from the integer set. (If the integer set don't have any integer ii, don't do anything.)
C ii : Count. Count the occurrence of integer ii in the integer set, output the number. (If the integer set doesn't have any integer ii, output "0".)
*/