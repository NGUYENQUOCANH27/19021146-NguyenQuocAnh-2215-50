#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int n;
    cin >> n;

    int sqrt_n = static_cast<int>(sqrt(n));
    if (sqrt_n * sqrt_n == n) {
        cout << "YES" << std::endl;
    } else {
        cout << "NO" << std::endl;
    }

    return 0;
}
