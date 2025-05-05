#include <iostream>
#include <vector>
#include <climits>
using namespace std;

void matrixChainOrder(const vector<int>& p) {
    int n = p.size() - 1; // number of matrices
    vector<vector<int>> m(n, vector<int>(n, 0));

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                int cost = m[i][k] + m[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
                if (cost < m[i][j]) {
                    m[i][j] = cost;
                }
            }
        }
    }

    cout << "\nMinimum number of multiplications: " << m[0][n - 1] << endl;
}

int main() {
    int n;
    cout << "Enter number of matrices: ";
    cin >> n;

    vector<int> p(n + 1);
    cout << "Enter dimensions (p0 p1 p2 ... p" << n << "): ";
    for (int i = 0; i <= n; i++) {
        cin >> p[i];
    }

    matrixChainOrder(p);

    return 0;
}
