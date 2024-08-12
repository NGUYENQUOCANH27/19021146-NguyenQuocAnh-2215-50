#include <iostream>
using namespace std;

class Rectangle {
public:
    int height, length;

    Rectangle(int h = 0, int l = 0) : height(h), length(l) {}

    int getPerimeter() const {
        return 2 * (height + length);
    }

    void print() const {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < length; j++) {
                cout << "*";
            }
            cout << endl;
        }
    }
};

int compare(const Rectangle &a, const Rectangle &b) {
    int perimeterA = a.getPerimeter();
    int perimeterB = b.getPerimeter();
    if (perimeterA < perimeterB) return -1;
    else if (perimeterA > perimeterB) return 1;
    else return 0;
}

