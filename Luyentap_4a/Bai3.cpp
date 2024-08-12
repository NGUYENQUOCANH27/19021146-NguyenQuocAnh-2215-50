#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

class Complex {
public:
    int a, b;

    Complex() : a(0), b(0) {}

    Complex(int real, int imag) : a(real), b(imag) {}

    void print() {
        if (a == 0 && b == 0) {
            cout << "0\n";
            return;
        }

        if (a != 0) {
            cout << a;
        }

        if (b > 0) {
            cout << "+" << b << "i\n";
        } else if (b < 0) {
            cout << b << "i\n";
        } else {
            cout << "\n";
        }
    }

    double abs() {
        return sqrt(a * a + b * b);
    }
};

Complex add(Complex x, Complex y) {
    Complex result;
    result.a = x.a + y.a;
    result.b = x.b + y.b;
    return result;
}


