#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    long long n;
    cin >> n;
    vector<pair<long long, long long>> steps(n);

    for (long long i = 0; i < n; ++i) {
        cin >> steps[i].first >> steps[i].second;
    }

    long long max_a = 0, max_b = 0;
    for (const auto& step : steps) {
        max_a = max(max_a, step.first);
        max_b = max(max_b, step.second);
    }

    vector<vector<long long>> grid(max_a + 1, vector<long long>(max_b + 1, 0));

    for (const auto& step : steps) {
        for (long long i = 1; i <= step.first; ++i) {
            for (long long j = 1; j <= step.second; ++j) {
                grid[i][j]++;
            }
        }
    }

    long long X = 0;
    for (long long i = 1; i <= max_a; ++i) {
        for (long long j = 1; j <= max_b; ++j) {
            X = max(X, grid[i][j]);
        }
    }

    long long count_X = 0;
    for (long long i = 1; i <= max_a; ++i) {
        for (long long j = 1; j <= max_b; ++j) {
            if (grid[i][j] == X) {
                count_X++;
            }
        }
    }

    cout << (long long)count_X << endl;

    return 0;
}
