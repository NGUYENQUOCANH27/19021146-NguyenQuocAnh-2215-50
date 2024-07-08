#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    vector<int> arr(n);
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    sort(arr.begin(), arr.end());

    int min_diff = abs(arr[1] - arr[0]);
    for(int i = 1; i < n - 1; i++) {
        int diff = abs(arr[i + 1] - arr[i]);
        if(diff < min_diff) {
            min_diff = diff;
        }
    }

    cout << min_diff << endl;

    return 0;
}
