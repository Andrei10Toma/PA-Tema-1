#include <bits/stdc++.h>
#define MAX_N 100
#define MAX_B 500
#define MAX_L 100
using namespace std;

struct Stock {
    int current_value;
    int min_value;
    int max_value;
    Stock(int _current_value, int _min_value, int _max_value)
        : current_value(_current_value)
        , min_value(_min_value)
        , max_value(_max_value) {}
};

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n, b, l;
    vector<Stock> stocks;

    void read_input() {
        ifstream fin("stocks.in");
        fin >> n;
        fin >> b;
        fin >> l;
        int current_value, min_value, max_value;
        for (int i = 0; i < n; i++) {
            fin >> current_value;
            fin >> min_value;
            fin >> max_value;
            stocks.push_back(Stock(current_value, min_value, max_value));
        }
    }

    int stock() {
        // n - number of stocks
        // b - budget
        // l - max loss
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(b + 1,
        vector<int>(l + 1)));
        int i, j, k, max_profit = 0;
        // base case (n = 0)
        for (i = 0; i <= b; i++) {
            for (j = 0; j <= l; j++) {
                dp[0][i][j] = 0;
            }
        }
        // base case (b = 0)
        for (i = 0; i <= n; i++) {
            for (j = 0; j <= l; j++) {
                dp[i][0][j] = 0;
            }
        }
        // base case (l = 0)
        for (i = 0; i <= n; i++) {
            for (j = 0; j <= b; j++) {
                dp[i][j][0] = 0;
            }
        }
        // i - stock order number
        // j - actual budget
        // k - loss
        for (i = 1; i <= n; i++) {
            for (j = 1; j <= b; j++) {
                for (k = 1; k <= l; k++) {
                    // not enough actual budget
                    if (stocks[i - 1].current_value > j) {
                        dp[i][j][k] = dp[i - 1][j][k];
                    } else {
                        //  potential loss for the stock
                        int loss = stocks[i - 1].current_value -
                            stocks[i - 1].min_value;
                        // the potential loss is bigger than the maximum
                        // accepted loss
                        if (loss > k) {
                            dp[i][j][k] = dp[i - 1][j][k];
                            continue;
                        }
                        // the potential profit for the stock
                        int profit = stocks[i - 1].max_value -
                            stocks[i - 1].current_value;
                        // remaining budget after the stock is bought
                        int remaining = j - stocks[i - 1].current_value;
                        // update the max value on the current field
                        dp[i][j][k] = max(dp[i - 1][j][k],
                            dp[i - 1][remaining][k - loss] + profit);
                    }
                    // extract the from all of the cells
                    if (dp[i][j][k] > max_profit) max_profit = dp[i][j][k];
                }
            }
        }
        return max_profit;
    }

    int get_result() { return stock(); }

    void print_output(int result) {
        ofstream fout("stocks.out");
        fout << result;
        fout.close();
    }
};

int main() {
    auto* task = new (std::nothrow) Task();
    if (!task) {
        std::cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
