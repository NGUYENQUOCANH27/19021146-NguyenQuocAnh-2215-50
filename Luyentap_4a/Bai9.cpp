#include <iostream>
#include <string>
using namespace std;

string decimal_to_binary(long number) {
    string binary = "";
    while (number > 0) {
        binary = to_string(number % 2) + binary;
        number /= 2;
    }
    return binary;
}

