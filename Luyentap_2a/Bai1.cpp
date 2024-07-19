#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> A(n);
    for (int i = 0; i < n; ++i) {
        cin >> A[i];
    }

    sort(A.begin(), A.end());

    int max_count = 1;
    int current_count = 1;

    for (int i = 1; i < n; ++i) {
        if (A[i] - A[i - 1] <= 1) {
            ++current_count;
        } else {
            max_count = max(max_count, current_count);
            current_count = 1;
        }
    }

    max_count = max(max_count, current_count);

    cout << max_count << endl;

    return 0;
}
