#include <bits/stdc++.h>
using namespace std;

struct Peek {
    long long int height;
    long long int cost;

    Peek(long long int _height, long long int _cost)
        : height(_height)
        , cost(_cost) {}
};

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    unsigned int n;
    vector<Peek> mountain;

    void read_input() {
        ifstream fin("ridge.in");
        fin >> n;
        long long int height, cost;
        for (unsigned int i = 0; i < n; i++) {
            fin >> height;
            fin >> cost;
            mountain.push_back(Peek(height, cost));
        }
    }

    long long int ridge() {
        unsigned int i;
        // the vector is a vector of triplets
        // a peek can be digged maximum 2 times, to achieve a minimum cost
        // first element - the cost if the peek is not digged
        // second element - the cost if the peek is digged one time
        // third element - the cost if the peek is digged two times
        vector<pair<long long int,
            pair<long long int, long long int>>> dp(n);
        // base case
        if (mountain[0].height > 1) {
            dp[0] = make_pair(0, make_pair(mountain[0].cost,
                2 * mountain[0].cost));
        } else {
            dp[0] = make_pair(0, make_pair(mountain[0].cost,
                LONG_LONG_MAX));
        }
        for (i = 1; i < n; i++) {
            dp[i].first = LONG_LONG_MAX;
            dp[i].second.first = LONG_LONG_MAX;
            dp[i].second.second = LONG_LONG_MAX;
            // find the best choice (lowest cost one) without digging the
            // current peek and digging just the previous peek if it is needed
            if (mountain[i].height != mountain[i - 1].height) {
                dp[i].first = min(dp[i].first, dp[i - 1].first);
            }
            if (mountain[i].height != mountain[i - 1].height - 1) {
                dp[i].first = min(dp[i].first, dp[i - 1].second.first);
            }
            // check if the dig in the previous peek can be done
            if (mountain[i - 1].height - 2 >= 0 &&
                mountain[i].height != mountain[i - 1].height - 2) {
                dp[i].first = min(dp[i].first, dp[i - 1].second.second);
            }
            // find the best choice (lowest cost one) digging only one time in
            // the current peek and digging in the previous peek if it is needed
            if (mountain[i].height - 1 != mountain[i - 1].height) {
                dp[i].second.first = min(dp[i].second.first, dp[i - 1].first);
            }
            if (mountain[i].height - 1 != mountain[i - 1].height - 1) {
                dp[i].second.first = min(dp[i].second.first,
                    dp[i - 1].second.first);
            }
            // check if the dig in the previous peek can be done
            if (mountain[i - 1].height - 2 >= 0 &&
                mountain[i].height - 1 != mountain[i - 1].height - 2) {
                dp[i].second.first = min(dp[i].second.first,
                    dp[i - 1].second.second);
            }
            // after the minimum cost is found add the current peek cost to the
            // found minimum
            dp[i].second.first += mountain[i].cost;
            // check if the current peek can be digged two times into it
            if (mountain[i].height - 2 >= 0) {
                // find the best choice (lowest cost one) digging two times in
                // the current peek and digging in the previous peek 
                if (mountain[i].height - 2 != mountain[i - 1].height) {
                    dp[i].second.second = min(dp[i].second.second,
                        dp[i - 1].first);
                }
                if (mountain[i].height - 2 != mountain[i - 1].height - 1) {
                    dp[i].second.second = min(dp[i].second.second,
                        dp[i - 1].second.first);
                }
                // check if the previous peek can be digged two times
                if (mountain[i - 1].height - 2 >= 0 &&
                    mountain[i].height - 2 != mountain[i - 1].height - 2) {
                    dp[i].second.second = min(dp[i].second.second,
                        dp[i - 1].second.second);
                }
                // after the minimum cost is found add the current peek cost to
                // the found minimum
                dp[i].second.second += 2 * mountain[i].cost;
            }
        }
        return (min(dp[n - 1].first, min(dp[n - 1].second.first,
            dp[n - 1].second.second)));
    }

    long long int get_result() { return ridge(); }

    void print_output(long long int result) {
        ofstream fout("ridge.out");
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
