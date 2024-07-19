#include <iostream>
#include <algorithm>
using namespace std;

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int main() {
    int tuSo, mauSo;
    cin >> tuSo >> mauSo;
    
    int ucln = gcd(abs(tuSo), abs(mauSo));
    
    tuSo /= ucln;
    mauSo /= ucln;
    
    if (mauSo < 0) {
        tuSo = -tuSo;
        mauSo = -mauSo;
    }
    
    if (mauSo == 1) {
        cout << tuSo << endl;
    } else {
        cout << tuSo << "/" << mauSo << endl;
    }
    
    return 0;
}
