#include <iostream>
#include <algorithm>
using namespace std;

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int lcm(int a, int b) {
    if (a == 0 || b == 0) {
        return 0;
    }
    return (a / gcd(a, b)) * b;
}

int main() {
    int a, b;
    cin >> a >> b;
    
    int result = lcm(a, b);
    if (result == 0) {
        cout << "0" << endl;
    } else {
        cout <<  abs(result) << endl;
    }

    return 0;
}
