#include <iostream>
#include <cstring>
using namespace std;

void reverse(char *s) {
    char *left = s;
    char *right = s + strlen(s) - 1;
    while(left < right) {
        int temp = *left;
        *left = *right;
        *right = temp;
        left++;
        right--;
    }
}