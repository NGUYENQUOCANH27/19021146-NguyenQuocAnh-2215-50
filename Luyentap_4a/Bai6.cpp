#include <iostream>
using namespace std;

int** transpose(int** matrix, int nRows, int nCols) {
    int** transposedMatrix = new int*[nCols]; 
    for (int i = 0; i < nCols; ++i) {
        transposedMatrix[i] = new int[nRows]; 
    }

    for (int i = 0; i < nRows; ++i) {
        for (int j = 0; j < nCols; ++j) {
            transposedMatrix[j][i] = matrix[i][j];
        }
    }

    return transposedMatrix;
}

void printMatrix(int** matrix, int nRows, int nCols) {
    for (int i = 0; i < nRows; ++i) {
        for (int j = 0; j < nCols; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
