#include <iostream>
#include <cmath>
using namespace std;

int gcd(int a, int b) {
    if (b == 0) {
        return abs(a);
    }
    return gcd(b, a % b);
}

int main() {
    int tu, mau;
    cin >> tu >> mau;
    int ucln = gcd(tu, mau);
    tu /= ucln;
    mau /= ucln;
    if (mau == 1) {
        cout << tu << endl;
    } else if (mau == -1) {
        cout << -tu << endl;
    } else if (tu == 0) {
        cout << "0" << endl;
    } else {
        cout << tu << "/" << mau << endl;
    }
    return 0;
}