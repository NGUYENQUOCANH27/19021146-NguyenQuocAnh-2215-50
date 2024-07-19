#include <iostream>
#include <cstdlib> 
#include <ctime>  
using namespace std;

int myRandom(int n) {
    srand(time(0));
    return rand() % n;
}

