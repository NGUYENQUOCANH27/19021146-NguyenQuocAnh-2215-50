#include <iostream>
#include <unordered_set>
using namespace std;

int main() {
    int m, n;
    cin >> m >> n;
    unordered_set<int> a1;
    int temp;
    for (int i = 0; i < m; i++) {
        cin >> temp;
        a1.insert(temp);
    }
    bool isSubset = true;
    for (int i = 0; i < n; i++) {
        cin >> temp;
        if (a1.find(temp) == a1.end()) {
            isSubset = false;
            break;
        }
    }
    if (isSubset) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}