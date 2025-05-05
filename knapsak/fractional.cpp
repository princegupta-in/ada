#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Item {
    double value, weight;

    // Value to weight ratio
    double ratio() const {
        return value / weight;
    }
};

// Compare items by value-to-weight ratio
bool compare(Item a, Item b) {
    return a.ratio() > b.ratio();
}

double fractionalKnapsack(int capacity, vector<Item>& items) {
    sort(items.begin(), items.end(), compare);

    double totalValue = 0.0;

    for (const auto& item : items) {
        if (capacity >= item.weight) {
            capacity -= item.weight;
            totalValue += item.value;
        } else {
            totalValue += item.ratio() * capacity;
            break;
        }
    }

    return totalValue;
}

int main() {
    int n, capacity;
    cout << "Enter number of items: ";
    cin >> n;

    vector<Item> items(n);
    cout << "Enter value and weight of each item:\n";
    for (int i = 0; i < n; i++) {
        cin >> items[i].value >> items[i].weight;
    }

    cout << "Enter knapsack capacity: ";
    cin >> capacity;

    double maxValue = fractionalKnapsack(capacity, items);
    cout << "\nMaximum value in knapsack = " << maxValue << endl;

    return 0;
}