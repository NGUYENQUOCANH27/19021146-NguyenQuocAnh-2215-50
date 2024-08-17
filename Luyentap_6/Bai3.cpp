#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> A(n), B(n);
    unordered_set<int> setA, setB;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
        setA.insert(A[i]);
    }
    for (int i = 0; i < n; i++) {
        cin >> B[i];
        setB.insert(B[i]);
    }
    int sum = 0;
    for (int i = 0; i < n; i++) {
        if (setB.find(A[i]) == setB.end()) {
            sum += A[i];
        }
    }
    for (int i = 0; i < n; i++) {
        if (setA.find(B[i]) == setA.end()) {
            sum += B[i];
        }
    }
    cout << sum << endl;
    return 0;
}