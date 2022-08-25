#include <iostream>

using namespace std;

bool bi_search(long long int arr[], int n, long long int value) {
    int left = 0, right = n - 1;
    while(left <= right) {
        int mid = (left + right) / 2;
        if(arr[mid] == value)
            return true;
        else if(arr[mid] < value)   right = mid - 1; // search left side
        else    left = mid + 1; // search right side
    }
    return false;
}

int main () {
    int n, m;
    /* non-increasing integer array */
    long long int arr[100001], query;
    cin >> n >> m;
    for(int i = 0; i < n; i++) cin >> arr[i];

    while(m--) {
        cin >> query;
        if(bi_search(arr, n, query))    cout << "Y ";
        else    cout << "N ";
    }
    cout << endl;
    return 0;
}