# include <iostream>
# include <vector>

using namespace std;
using Iter = vector<long long int>::iterator;


/* print array */
void print_arr(vector <long long int> &a) {
    Iter i = a.begin();
    cout << *i;
    i++;
    for(; i != a.end(); i++)
        cout << " " << *i;
    cout << endl;
    return;
}

/* merge two array, one is [left, mid) and the other is [mid, right), the result is [left, right) */
void merge(Iter left, Iter mid, Iter right) {
    vector <long long int> temp;
    Iter p1, p2;
    for(p1 = left, p2 = mid; p1 != mid && p2 != right;) {
        if(*p1 >= *p2) {
            temp.push_back(*p1);
            p1++;
        }
        else {
            temp.push_back(*p2);
            p2++;
        }
    }

    for(; p1 != mid; p1++)
        temp.push_back(*p1);
    
    for(; p2 != right; p2++)
        temp.push_back(*p2);
    
    /* copy temp to original array */
    for(Iter i = temp.begin(), j = left; i != temp.end(); i++, j++)
        *j = *i;

    return;        
}

void mergesort(Iter left, Iter right) {
    if(right - left == 1)   return;
    Iter mid = left + (right - left) / 2;
    mergesort(left, mid);
    mergesort(mid, right);
    merge(left, mid, right);
}

int main() {
    long long int n;
    cin >> n;
    vector <long long int> a(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];
    
    mergesort(a.begin(), a.end());
    print_arr(a);
    return 0;
}