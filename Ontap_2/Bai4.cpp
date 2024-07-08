#include <iostream>
#include <limits>
using namespace std;

int main() {
    int n;
    cin >> n;

    double maxVal = numeric_limits<double>::lowest();
    double minVal = numeric_limits<double>::max();
    double currentValue;

    for (int i = 0; i < n; i++) {
        cin >> currentValue;
        if (currentValue > maxVal) {
            maxVal = currentValue;
        }
        if (currentValue < minVal) {
            minVal = currentValue;
        }
    }

    cout << maxVal << endl;
    cout << minVal << endl;

    return 0;
}