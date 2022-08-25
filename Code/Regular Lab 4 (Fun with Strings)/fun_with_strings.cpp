#include <iostream>
#include <string>
#include <vector>

#define ROLLING 23 // big enough to cover a~z
#define BUCKET 131 // big prime number
#define MAX_N 101
using namespace std;

int rolling_hash(const string &s, int rolling) {
    /* power of ROLLING can be stored in an array, we don't need to calculate it every time*/
    int times = 1;
    int sum = 0;
    for(int i = 0; i < s.length(); i++) {
        sum += ((int) s[i] * times) % BUCKET;
        times = (times *rolling) % BUCKET;
    }
    return sum % BUCKET;
}

int main() {
    int n, q;
    cin >> n >> q;
    vector <string> str_arr(n + 1);
    int hash_str[MAX_N];

    for(int t = 1; t <= n; t++) {
        cin >> str_arr[t];
        hash_str[t] = rolling_hash(str_arr[t], ROLLING);
    }
    
    char cmd;
    int i, j;

    while(q--) {
        cin >> cmd >> i >> j;
        if(cmd == 'E') {
            // E: check si sj are identical 
            if(hash_str[i] != hash_str[j])
                cout << "N" << endl;
            else {
                // need to compare two str 
                if(!str_arr[i].compare(str_arr[j]))  cout << "Y" << endl;
                else    cout << "N" << endl;
            }
        }
        else {
            // C: si = si + sj 
            str_arr[i] = str_arr[i] + str_arr[j];
            hash_str[i] = rolling_hash(str_arr[i], ROLLING); 
            /* rolling_hash's proterty: h(i+j) = ROLLING^(len(j))*h(i) + h(j), so we don't need to rehash it */
        }
    }

    return 0;
}
