#include <bits/stdc++.h>
#define MAX_P 1000000000
using namespace std;

struct Computer {
    int upgrade_cost;
    int power;
    Computer(int _upgrade_cost, int _power)
        : upgrade_cost(_upgrade_cost)
        , power(_power) {}
};

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n, b;
    vector<Computer> computers;

    void read_input() {
        ifstream fin("crypto.in");
        fin >> n;
        fin >> b;
        int upgrade_cost, power;
        for (int i = 0; i < n; i++) {
            fin >> power;
            fin >> upgrade_cost;
            computers.push_back(Computer(upgrade_cost, power));
        }
    }

    int crypto() {
        long long int max_profit = 0, left_p = 0, right_p = MAX_P, mid, i, sum;
        while (left_p <= right_p) {
            sum = b;
            // find the middle of the interval (mid is the max power)
            mid = right_p + (left_p - right_p) / 2;
            // for every computer check if the upgrade is possible
            for (i = 0; i < n; i++) {
                // if the upgrade has to be made
                if (computers[i].power < mid) {
                    sum -= (mid - computers[i].power)
                        * computers[i].upgrade_cost;
                    // not enough money
                    if (sum < 0) {
                        right_p = mid - 1;
                        break;
                    }
                }
            }
            // possible upgrade
            if (sum >= 0) {
                max_profit = mid;
                left_p = mid + 1;
            }
        }
        return max_profit;
    }

    int get_result() { return crypto(); }

    void print_output(int result) {
        ofstream fout("crypto.out");
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
