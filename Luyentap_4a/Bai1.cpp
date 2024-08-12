#include <iostream>
#include <cmath>
using namespace std;

struct Point {
    double x, y;

    Point() : x(0), y(0) {}  
    Point(double x, double y) : x(x), y(y) {}  
    Point(const Point& p) : x(p.x), y(p.y) {}  
};

class Triangle {
    Point p1, p2, p3;

public:
    Triangle(const Point &a, const Point &b, const Point &c) : p1(a), p2(b), p3(c) {}

    double getPerimeter() const {
        double side1 = sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
        double side2 = sqrt(pow(p3.x - p2.x, 2) + pow(p3.y - p2.y, 2));
        double side3 = sqrt(pow(p1.x - p3.x, 2) + pow(p1.y - p3.y, 2));
        return side1 + side2 + side3;
    }

    double getArea() const {
        double a = sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
        double b = sqrt(pow(p3.x - p2.x, 2) + pow(p3.y - p2.y, 2));
        double c = sqrt(pow(p1.x - p3.x, 2) + pow(p1.y - p3.y, 2));
        double s = (a + b + c) / 2;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }
};

