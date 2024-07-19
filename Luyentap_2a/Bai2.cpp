#include <iostream>
using namespace std;

void printMatrix(int n) {
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cout << (i + j) % n + 1;
            if (j < n - 1) cout << " ";
        }
        cout << endl;
    }
}

int main() {
    int n;
    cin >> n;
    if(n > 0 && n < 100) {
        printMatrix(n);
    } else {
        cout << endl;
    }
    return 0;
}