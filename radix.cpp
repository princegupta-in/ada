#include <iostream>
#include <vector>
#include <climits>
using namespace std;

void countSort(vector<int> &v, int pos) {
    int n = v.size();

    // create frequency array
    vector<int> freq(10, 0);
    for (int i = 0; i < n; i++) {
        freq[(v[i] / pos) % 10]++;
    }

    // cumulative frequency
    for (int i = 1; i < 10; i++) {
        freq[i] += freq[i - 1];
    }

    // create the sorted array
    vector<int> ans(n);
    for (int i = n - 1; i >= 0; i--) {
        ans[--freq[(v[i] / pos) % 10]] = v[i];
    }

    // copy sorted elements back to original array
    for (int i = 0; i < n; i++) {
        v[i] = ans[i];
    }
}

void radixSort(vector<int> &v) {
    int max_ele = INT_MIN;

    // find the maximum element in the array
    for (auto x : v) {
        max_ele = max(x, max_ele);
    }

    // apply counting sort for every digit place (1s, 10s, 100s, ...)
    for (int pos = 1; max_ele / pos > 0; pos *= 10) {
        countSort(v, pos);
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

    radixSort(arr);
    //for each loop
    for(int val:arr){
        cout<<val<<" ";
    }
    return 0;
}
