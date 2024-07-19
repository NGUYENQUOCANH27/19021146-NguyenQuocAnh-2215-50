#include <iostream>
#include <cmath>
using namespace std;

bool is_prime(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int i = 3; i <= std::sqrt(n); i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

void print_prime(int n) {
    for (int i = 2; i < n; ++i) {
        if (is_prime(i)) {
            cout << i << endl;
        }
    }
}
