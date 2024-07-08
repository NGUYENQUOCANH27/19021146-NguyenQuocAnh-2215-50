#include <iostream>
#include <cmath>
using namespace std;

void checkTriangle(int a, int b, int c) {
    if (a + b > c && a + c > b && b + c > a) {
        int perimeter = a + b + c;
        cout << perimeter << endl;

        if (a == b && b == c) {
            cout << "deu" << endl; 
        } else if (a == b || b == c || a == c) {
            cout << "can" << endl; 
        } else if (pow(a, 2) + pow(b, 2) == pow(c, 2) ||
                   pow(a, 2) + pow(c, 2) == pow(b, 2) ||
                   pow(b, 2) + pow(c, 2) == pow(a, 2)) {
            cout << "vuong" << endl; 
        } else {
            cout << "thuong" << endl; 
        }
    } else {
        cout << "Invalid" << endl;
    }
}

int main() {
    int a, b, c;
    cin >> a >> b >> c;
    checkTriangle(a, b, c);
    return 0;
}
