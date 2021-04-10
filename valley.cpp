#include <bits/stdc++.h>
using namespace std;

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n;
    vector<unsigned long long int> mountain;

    void read_input() {
        ifstream fin("valley.in");
        fin >> n;
        int peak;
        for (int i = 0; i < n; i++) {
            fin >> peak;
            mountain.push_back(peak);
        }
    }

    unsigned long long int  valley() {
        unsigned int i, j;
        unsigned long long int min_hours = 0;
        // set the second peek of the mountain and the penultimae peek of the
        // mountain, so that the valley will have at least two peeks for the
        // prefix and the sufix
        if (mountain[1] > mountain[0]) {
            min_hours += mountain[1] - mountain[0];
            mountain[1] = mountain[0];
        }
        if (mountain[n - 2] > mountain[n - 1]) {
            min_hours += mountain[n - 2] - mountain[n - 1];
            mountain[n - 2] = mountain[n - 1];
        }
        vector<unsigned long long int> copy_mountain(mountain);
        vector<unsigned long long int> time_ascending;
        vector<unsigned long long int> time_decreasing;
        // base case for the calculus of the partial times
        time_decreasing.push_back(0);
        time_ascending.push_back(0);
        // calculate the partial time for every mountain peek to be decreasing
        // so the split of the mountain will be on the peultimate peek
        for (i = 2, j = 1; i < n - 2; i++, j++) {
            if (copy_mountain[i] > copy_mountain[i - 1]) {
                time_decreasing.push_back(time_decreasing[j - 1] +
                    copy_mountain[i] - copy_mountain[i - 1]);
                copy_mountain[i] = copy_mountain[i - 1];
            } else {
                time_decreasing.push_back(time_decreasing[j - 1]);
            }
        }
        // calculate the partial time for every mountain peek to be ascending
        // so the split of the mountain will be on the second peek
        for (i = n - 3, j = 1; i >= 2; i--, j++) {
            if (mountain[i] > mountain[i + 1]) {
                time_ascending.push_back(time_ascending[j - 1] +
                    mountain[i] - mountain[i + 1]);
                mountain[i] = mountain[i + 1];
            } else {
                time_ascending.push_back(time_ascending[j - 1]);
            }
        }
        unsigned int sums_length = time_decreasing.size();
        long long unsigned int min_split = LONG_LONG_MAX;
        // choose the best place where to split the prefix and the sufix
        for (i = 0, j = sums_length - 1; i < sums_length && j >= 0; i++, j--) {
            if (time_decreasing[i] + time_ascending[j] < min_split) {
                min_split = time_decreasing[i] + time_ascending[j];
            }
        }
        return min_hours + min_split;
    }

    unsigned long long int get_result() { return valley(); }

    void print_output(unsigned long long int result) {
        ofstream fout("valley.out");
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
