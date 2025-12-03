#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

void _01_knapsack(int W, vector<int>& wt, vector<int>& val, int n) {
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (wt[i - 1] <= w) {
                dp[i][w] = max(dp[i - 1][w], val[i - 1] + dp[i - 1][w - wt[i - 1]]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    cout << "Maximum value in Knapsack = " << dp[n][W] << endl;
}
int main() {
    int W = 50; // Maximum weight of knapsack
    vector<int> wt = {10, 20, 30}; // Weights of items
    vector<int> val = {60, 100, 120}; // Values of items
    int n = wt.size(); // Number of items

    _01_knapsack(W, wt, val, n);

    return 0;
}
