#include <iostream>
#include <string>
using namespace std;

int main() {
    string s;
    cin >> s;

    int i = 0;
    int j = s.length() - 1;
    bool isPalindrome = true;

    while (i < j) {
        if (s[i] != s[j]) {
            isPalindrome = false;
            break;
        }
        i++;
        j--;
    }

    if (isPalindrome) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    return 0;
}
