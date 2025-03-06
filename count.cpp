#include <iostream>
#include <vector>
#include <climits>
using namespace std;

void countSort(vector<int> &v) {
    int n = v.size();

    // find the max element
    int max_ele = INT_MIN;
    for (int i = 0; i < n; i++) {
        max_ele = max(v[i], max_ele);
    }

    // frequency array
    vector<int> freq(max_ele + 1, 0);
    for (int i = 0; i < n; i++) {
        freq[v[i]]++;
    }

    // cumulative frequency
    for (int i = 1; i <= max_ele; i++) {
        freq[i] += freq[i - 1];
    }

    // sorted array
    vector<int> ans(n);
    for (int i = n - 1; i >= 0; i--) {
        ans[--freq[v[i]]] = v[i];
    }

    // Copy back the sorted elements
    for (int i = 0; i < n; i++) {
        v[i] = ans[i];
    }
}


int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;
    vector<int>arr(n);
    cout<<"enter all elements: ";
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }

    countSort(arr);
    //for each loop
    for(int val:arr){
        cout<<val<<" ";
    }
    return 0;
}
