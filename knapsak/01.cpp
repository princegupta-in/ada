#include <iostream>
#include <vector>
using namespace std;

int knapsack01(int n, int capacity, const vector<int>& weights, const vector<int>& values) {
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    // Build DP table
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (weights[i - 1] <= w) {
                dp[i][w] = max(
                    values[i - 1] + dp[i - 1][w - weights[i - 1]],  // include item
                    dp[i - 1][w]                                   // exclude item
                );
            } else {
                dp[i][w] = dp[i - 1][w]; // can't include item
            }
        }
    }

    return dp[n][capacity];
}

int main() {
    int n, capacity;
    cout << "Enter number of items: ";
    cin >> n;

    vector<int> weights(n), values(n);
    cout << "Enter weights of items:\n";
    for (int i = 0; i < n; i++) {
        cin >> weights[i];
    }

    cout << "Enter values of items:\n";
    for (int i = 0; i < n; i++) {
        cin >> values[i];
    }

    cout << "Enter knapsack capacity: ";
    cin >> capacity;

    int maxVal = knapsack01(n, capacity, weights, values);
    cout << "\nMaximum value in knapsack = " << maxVal << endl;

    return 0;
}
