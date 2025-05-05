#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Counting Sort function for sorting individual buckets
void countingSort(vector<int>& bucket) {
    if (bucket.empty()) return;

    int maxVal = *max_element(bucket.begin(), bucket.end());
    int minVal = *min_element(bucket.begin(), bucket.end());
    int range = maxVal - minVal + 1;

    vector<int> count(range, 0);
    vector<int> output(bucket.size());

    for (int num : bucket) {
        count[num - minVal]++;
    }

    for (int i = 1; i < range; i++) {
        count[i] += count[i - 1];
    }

    for (int i = bucket.size() - 1; i >= 0; i--) {
        output[count[bucket[i] - minVal] - 1] = bucket[i];
        count[bucket[i] - minVal]--;
    }

    for (size_t i = 0; i < bucket.size(); i++) {
        bucket[i] = output[i];
    }
}

// Bucket Sort using Counting Sort
void bucketSort(vector<int>& arr, int bucketSize) {
    if (arr.empty()) return;

    int minVal = *min_element(arr.begin(), arr.end());
    int maxVal = *max_element(arr.begin(), arr.end());

    int bucketCount = (maxVal - minVal) / bucketSize + 1;
    vector<vector<int>> buckets(bucketCount);

    for (int num : arr) {
        int index = (num - minVal) / bucketSize;
        buckets[index].push_back(num);
    }

    for (vector<int>& bucket : buckets) {
        countingSort(bucket);
    }

    int index = 0;
    for (const vector<int>& bucket : buckets) {
        for (int num : bucket) {
            arr[index++] = num;
        }
    }
}

// Driver function
int main() {
    int n, bucketSize;
    cout << "Enter the number of elements: ";
    cin >> n;
    vector<int> arr(n);

    cout << "Enter " << n << " integers: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << "Enter bucket size: ";
    cin >> bucketSize;

    bucketSort(arr, bucketSize);

    cout << "Sorted array: ";
    for (int num : arr) cout << num << " ";
    cout << endl;

    return 0;
}
