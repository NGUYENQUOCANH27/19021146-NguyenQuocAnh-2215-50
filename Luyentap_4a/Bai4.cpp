#include <iostream>
using namespace std;

struct Time {
    int h; 
    int m; 
    int s; 

    Time() : h(0), m(0), s(0) {}

    Time(int hours, int minutes, int seconds) : h(hours), m(minutes), s(seconds) {}

    int second() {
        return h * 3600 + m * 60 + s;
    }

    void print() {
        printf("%02d:%02d:%02d\n", h, m, s);
    }
};

Time normalize(int h, int m, int s) {
    m += s / 60; 
    s %= 60;
    h += m / 60; 
    m %= 60;
    return Time(h, m, s);
}

