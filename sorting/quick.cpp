#include <iostream>
#include <vector>
using namespace std;

int partition(vector<int> &arr, int st, int end) {
    int idx = st - 1, pivot = arr[end];

    for (int j = st; j < end; j++) {
        if (arr[j] <= pivot) {
            idx++;
            swap(arr[j], arr[idx]);
        }
    }

    idx++;
    swap(arr[end], arr[idx]);
    return idx;
}

void quickSort(vector<int> &arr, int st, int end) {
    if (st < end) {
        int pivIdx = partition(arr, st, end);

        quickSort(arr, st, pivIdx - 1);  // left half
        quickSort(arr, pivIdx + 1, end); // right half
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

    quickSort(arr,0,arr.size()-1);
    //for each loop
    for(int val:arr){
        cout<<val<<" ";
    }
    return 0;
}
