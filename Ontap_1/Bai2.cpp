#include <iostream>
using namespace std;

int main() {
    double a1, b1, c1, a2, b2, c2;
    cin >> a1 >> b1 >> c1 >> a2 >> b2 >> c2;

    double determinant = a1 * b2 - a2 * b1;
    if (determinant == 0) {
        if (a1 * c2 == a2 * c1 && b1 * c2 == b2 * c1) {
            cout << "Vo so nghiem";
        } else {
            cout << "Vo nghiem";
        }
    } else {
        double x = (c1 * b2 - c2 * b1) / determinant;
        double y = (a1 * c2 - a2 * c1) / determinant;
        cout << "x = " << x << ", y = " << y;
    }

    return 0;
}
