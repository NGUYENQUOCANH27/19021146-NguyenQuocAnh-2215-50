#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    double a, b, c;
    cin >> a >> b >> c;

    double delta = b * b - 4 * a * c;

    if (delta > 0) {
        double x1 = (-b + sqrt(delta)) / (2 * a);
        double x2 = (-b - sqrt(delta)) / (2 * a);
        if (x1 == x2) {
            cout << fixed << setprecision(2) << x1 << endl;
        } else {
            if (x1 > x2) {
                cout << fixed << setprecision(2) << x2 << endl;
                cout << fixed << setprecision(2) << x1 << endl;
            } else {
                cout << fixed << setprecision(2) << x1 << endl;
                cout << fixed << setprecision(2) << x2 << endl;
            }
        }
    } else if (delta == 0) {
        double x = -b / (2 * a);
        cout << fixed << setprecision(2) << x << endl;
    } else {
        double realPart = -b / (2 * a);
        double imaginaryPart = sqrt(-delta) / (2 * a);
        cout << fixed << setprecision(2) << realPart << " -" << imaginaryPart << endl;
        cout << fixed << setprecision(2) << realPart << " " << imaginaryPart << endl;
    }

    return 0;
}
