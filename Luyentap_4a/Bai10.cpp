#include <iostream>
#include <vector>
using namespace std;

void primeFactors(int n) {
    vector<int> factors;
    vector<int> powers;
    int count = 0;
    while (n % 2 == 0) {
        n /= 2;
        count++;
    }
    if (count > 0) {
        factors.push_back(2);
        powers.push_back(count);
    }
    for (int i = 3; i * i <= n; i += 2) {
        count = 0;
        while (n % i == 0) {
            n /= i;
            count++;
        }
        if (count > 0) {
            factors.push_back(i);
            powers.push_back(count);
        }
    }
    if (n > 2) {
        factors.push_back(n);
        powers.push_back(1);
    }
    for (size_t i = 0; i < factors.size(); i++) {
        cout << factors[i] << " " << powers[i] << endl;
    }
}
