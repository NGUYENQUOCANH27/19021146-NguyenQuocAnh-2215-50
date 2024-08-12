#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool isSubsequence(const vector<int>& a, const vector<int>& b) {
    int n = a.size();
    int m = b.size();
    int j = 0; 
    for (int i = 0; i < m && j < n; i++) {
        if (a[j] == b[i]) {
            j++;
        }
    }
    return (j == n);
}

int main() {
    int n, m, x;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    cin >> m;
    vector<int> b(m);
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }
    if (isSubsequence(a, b)) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
    return 0;
}
