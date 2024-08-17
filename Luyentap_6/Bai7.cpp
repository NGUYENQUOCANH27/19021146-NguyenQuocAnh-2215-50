#include <iostream>
#include <numeric> 
using namespace std;

class Fraction {
    int a, b;
public:
    Fraction(int a = 1, int b = 1) : a(a), b(b) {
        simplify();
    }
    friend ostream& operator<<(ostream& os, const Fraction& f) {
        if (f.b == 0) {
            os << "invalid";
        } else {
            os << f.a << "/" << f.b;
        }
        return os;
    }
    Fraction operator+(const Fraction& f) const {
        int num = a * f.b + f.a * b;
        int den = b * f.b;
        return Fraction(num, den);
    }
    Fraction operator-(const Fraction& f) const {
        int num = a * f.b - f.a * b;
        int den = b * f.b;
        return Fraction(num, den);
    }
    Fraction operator*(const Fraction& f) const {
        int num = a * f.a;
        int den = b * f.b;
        return Fraction(num, den);
    }
    Fraction operator/(const Fraction& f) const {
        int num = a * f.b;
        int den = b * f.a;
        return Fraction(num, den);
    }
    void simplify() {
        if (b == 0) {
            a = 0;
        } else {
            int gcd = gcd(a, b);
            a /= gcd;
            b /= gcd;
            if (b < 0) { 
                a = -a;
                b = -b;
            }
        }
    }
    bool operator>(const Fraction& f) const {
        return a * f.b > f.a * b;
    }
    bool operator<(const Fraction& f) const {
        return a * f.b < f.a * b;
    }
};
int main() {
    Fraction x(1, 3), y(1, 3);
    x = x + y;
    cout << x << endl; 
    return 0;
}
