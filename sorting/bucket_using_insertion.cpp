#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to perform Insertion Sort on a bucket
void insertionSort(vector<float>& bucket) {
    int n = bucket.size();
    for (int i = 1; i < n; i++) {
        float key = bucket[i];
        int j = i - 1;
        while (j >= 0 && bucket[j] > key) {
            bucket[j + 1] = bucket[j];
            j--;
        }
        bucket[j + 1] = key;
    }
}

// Function to perform Bucket Sort
void bucketSort(vector<float>& arr) {
    int n = arr.size();
    if (n <= 0) return;

    // Create empty buckets
    vector<vector<float>> buckets(n);

    // Insert elements into the appropriate buckets
    for (int i = 0; i < n; i++) {
        int bucketIndex = n * arr[i]; // Assuming input is in the range [0,1)
        buckets[bucketIndex].push_back(arr[i]);
    }

    // Sort each bucket using Insertion Sort
    for (int i = 0; i < n; i++) {
        insertionSort(buckets[i]);
    }

    // Concatenate all buckets into the original array
    int index = 0;
    for (int i = 0; i < n; i++) {
        for (float num : buckets[i]) {
            arr[index++] = num;
        }
    }
}

// Driver function
int main() {
    vector<float> arr = {0.42, 0.32, 0.33, 0.52, 0.25, 0.47, 0.51};

    cout << "Original array: ";
    for (float num : arr) cout << num << " ";
    cout << endl;

    bucketSort(arr);

    cout << "Sorted array: ";
    for (float num : arr) cout << num << " ";
    cout << endl;

    return 0;
}
