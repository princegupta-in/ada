#include <iostream>
#include <vector>
#include <algorithm> // for sort function

using namespace std;

void bucketSort(float arr[], int size) {
    // Step 1: Create empty buckets
    vector<vector<float>> bucket(size);

    // Step 2: Insert elements into buckets
    for (int i = 0; i < size; i++) {
        int index = arr[i] * size;  // Finding the appropriate bucket index
        bucket[index].push_back(arr[i]);
    }

    // Step 3: Sort individual buckets
    for (int i = 0; i < size; i++) {
        if (!bucket[i].empty()) {
            sort(bucket[i].begin(), bucket[i].end());
        }
    }

    // Step 4: Combine elements from buckets back to array
    int k = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < bucket[i].size(); j++) {
            arr[k++] = bucket[i][j];
        }
    }
}

int main() {
    float arr[] = {0.13, 0.45, 0.12, 0.89, 0.75, 0.63, 0.85, 0.39};
    int size = sizeof(arr) / sizeof(arr[0]);

    bucketSort(arr, size);

    // Print sorted array
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";

    return 0;
}
