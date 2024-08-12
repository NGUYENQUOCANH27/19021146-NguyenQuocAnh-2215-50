#include <iostream>
#include <cstring> 
using namespace std;

void Filter(char *s) {
    int len = strlen(s); 
    char *right = s + len - 1; 

    while (right >= s) { 
        if (!((*right >= 'a' && *right <= 'z') || (*right >= 'A' && *right <= 'Z'))) {
            *right = '-'; 
        }
        right--; 
    }
}
