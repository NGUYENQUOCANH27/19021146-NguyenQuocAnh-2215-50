#include <iostream>
#include <cstring>
using namespace std;

void rFilter(char *s) {
    char *right = s + strlen(s) - 1; 
    while (right >= s && !((*right >= 'a' && *right <= 'z') || (*right >= 'A' && *right <= 'Z'))) {
        *right = '_'; 
        right--;
    }
}

