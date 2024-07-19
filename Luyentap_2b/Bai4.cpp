#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> generateMagicSquare(int N) {
    vector<vector<int>> magicSquare(N, vector<int>(N, 0));
    
    int number = 1;
    int i = 0, j = N / 2;
    
    while (number <= N * N) {
        magicSquare[i][j] = number++;
        int newi = (i - 1 + N) % N;
        int newj = (j + 1) % N;
        
        if (magicSquare[newi][newj]) {
            i = (i + 1) % N;
        } else {
            i = newi;
            j = newj;
        }
    }
    
    return magicSquare;
}

void printMagicSquare(const vector<vector<int>>& magicSquare) {
    int N = magicSquare.size();
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << magicSquare[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int N;
    cin >> N;
    
    if (N % 2 == 0) {
        cout << endl;
        return 1;
    }
    
    vector<vector<int>> magicSquare = generateMagicSquare(N);
    printMagicSquare(magicSquare);
    
    return 0;
}
